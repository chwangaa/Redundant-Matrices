#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <emmintrin.h>
#include <immintrin.h>
#include "sparse_matrix.h"

static Dtype matrix_buffer[400*1600] __attribute__((aligned(0x1000)));
static Dtype buffer[2400] __attribute__((aligned(0x1000)));

static void readInNewPair(FILE* fin, i_j_pairs* pair){
	assert(fin != NULL);
	int num_i_values;
	int num_j_values;
	
	fscanf(fin, "%d ", &num_i_values);
	int* i_values = (int*)malloc(sizeof(int)*num_i_values);
	for(int i = 0; i < num_i_values; i++){
		int temp;
		fscanf(fin, "%d", &temp);
		i_values[i] = temp;
	}


	fscanf(fin, "%d ", &num_j_values);
	int* j_values = (int*)malloc(sizeof(int)*num_j_values);
	for(int i = 0; i < num_j_values; i++){
		int temp;
		fscanf(fin, "%d", &temp);
		j_values[i] = temp;
	}

	pair->i_values = i_values;
	pair->j_values = j_values;
	pair->num_i_values = num_i_values;
	pair->num_j_values = num_j_values;
}

static void readInNewScaler(FILE* fin, Scaler* new_s){
	assert(fin != NULL);
	Dtype scaler_value;
	int num_pairs;
	int num_rows_write_to;
	fscanf(fin, "%f %d %d", &scaler_value, &num_pairs, &num_rows_write_to);
	// fprintf(stderr, "the scaler has the value %f and the number of pairs is %d \n", scaler_value, num_pairs);
	// fprintf(stderr, "the number of rows write to is %d \n", num_rows_write_to);

	// read in all the i values
	int* union_i_values = (int*)malloc(sizeof(int)*num_rows_write_to);
	for(int i = 0; i < num_rows_write_to; i++){
		int temp;
		fscanf(fin, "%d", &temp);
		union_i_values[i] = temp;
	}
	new_s->i_values = union_i_values;


	// read in each set of i_j_pairs
	i_j_pairs* pairs = (i_j_pairs*)malloc(sizeof(i_j_pairs)*num_pairs);
	for(int i = 0; i < num_pairs; i++){
		readInNewPair(fin, &pairs[i]);
	}
	new_s->pairs = pairs;
	new_s->value = scaler_value;
	new_s->num_pairs = num_pairs;
	new_s->num_rows_write_to = num_rows_write_to;
}

SparseMatrix* init_SparseMatrix(const char* file_name){
	FILE* fin = fopen(file_name, "r");
	assert(fin != NULL);

	int rank;
	int row;
	int col;
	fscanf(fin, "%d %d %d", &row, &col, &rank);
	SparseMatrix* matrix = (SparseMatrix*)malloc(sizeof(SparseMatrix));

	Scaler* scalers = (Scaler*)malloc(sizeof(Scaler)*rank);
	
	for(int i = 0; i < rank; i++){
		// fprintf(stderr, "read the # %d scaler \n", i);
		readInNewScaler(fin, &scalers[i]);
	}
	matrix->rank = rank;
	matrix->scalers = scalers;
	matrix->col = col;
	matrix->row = row;
	// fprintf(stderr, "sparse matrix initialized \n");
	return matrix;
}

bool isInMatrix(SparseMatrix* m, Dtype value){
	Scaler* scalers = m->scalers;
	for(int i = 0; i < m->rank; i++){
		if(scalers[i].value == value){
			return 1;
		}
	}
	return 0;
}

unsigned int getNumberOfCol(SparseMatrix* m){
	return m->col;
}

unsigned int getNumberOfRow(SparseMatrix* m){
	return m->row;
}

unsigned int getNumberOfDistinctElement(SparseMatrix* m){
	return m->rank;
}

Scaler* getScalers(SparseMatrix* m){
	return m->scalers;
}

void scaleAlignedRow(int n, Dtype scaler, Dtype* A, const Dtype* B){
	__m256 scalar_ = _mm256_set1_ps(scaler);
	for(int i = 0; i < n; i+=8){
		__m256 As = _mm256_load_ps(A+i);
		__m256 Bs = _mm256_load_ps(B+i);
		__m256 Ms = _mm256_fmadd_ps(As, scalar_, Bs);
		_mm256_store_ps(B+i, Ms);
	}
	return;
}

void scaleUnAlignedRow(int n, Dtype scaler, Dtype* A, const Dtype* B){
	__m256 scalar_ = _mm256_set1_ps(scaler);
	for(int i = 0; i < n; i+=8){
		__m256 As = _mm256_load_ps(A+i);
		__m256 Bs = _mm256_loadu_ps(B+i);
		__m256 Ms = _mm256_fmadd_ps(As, scalar_, Bs);
		_mm256_storeu_ps(B+i, Ms);
	}
	return;
}

void set_row_to_zero(Dtype* row, int length){
	__m256 zeros_ = _mm256_set1_ps(0);
	for(int i = 0; i < length; i+=8){
		_mm256_store_ps(&row[i], zeros_);
	}
}

void initialize_matrix_buffer(Dtype* buffer, int num_rows_to_set, int* rows_to_set, int incRow){
	for(int i = 0; i < num_rows_to_set; i++){
		int row_number = rows_to_set[i];
		Dtype* row = &buffer[row_number*incRow];
		set_row_to_zero(row, incRow);
	}
}

void add_row_to_row(Dtype* source, Dtype* destination, int length){
	for(int i = 0; i < length; i+=8){
		__m256 r1 = _mm256_load_ps(source+i);
		__m256 r2 = _mm256_load_ps(destination+i);
		r1 = r1 + r2;			
		_mm256_store_ps(&destination[i], r1);
	}
}

void add_row_to_rows(const i_j_pairs pairs, Dtype* buffer, Dtype* matrix_buffer, int incRow){
	int num_i = pairs.num_i_values;
	int* is = pairs.i_values;
	for(int i = 0; i < num_i; i++){
		int r1 = is[i];
		Dtype* destination_row = &matrix_buffer[r1*incRow];
		add_row_to_row(buffer, destination_row, incRow);
	}
}

void scale_aligned_matrix(Dtype scaling_factor, Dtype* matrix_buffer, int num_rows_write_to, int* i_values, Dtype* C, int incRowC){

	assert(scaling_factor != 0);
	for(int i = 0; i < num_rows_write_to; i++){
		int row_n = i_values[i];
		Dtype* source_row = &matrix_buffer[row_n*incRowC];
		Dtype* destination_row = &C[row_n*incRowC];
		scaleAlignedRow(incRowC, scaling_factor, source_row, destination_row);
	}
}


void scale_unaligned_matrix(Dtype scaling_factor, Dtype* matrix_buffer, int num_rows_write_to, int* i_values, Dtype* C, int incRowC){

	assert(scaling_factor != 0);
	for(int i = 0; i < num_rows_write_to; i++){
		int row_n = i_values[i];
		Dtype* source_row = &matrix_buffer[row_n*incRowC];
		Dtype* destination_row = &C[row_n*incRowC];
		scaleUnAlignedRow(incRowC, scaling_factor, source_row, destination_row);
	}
}

void ScaleMatrixTo(Scaler s,
				   Dtype* B, int nrow, int ncol, int incRowB,
				   Dtype* C, int M, int N, int incRowC){

	

	// initialize a matrix buffer
	// assert(incRowB == N);
	// Dtype* matrix_buffer = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N, 32);
	int* i_values = s.i_values;
	int num_rows_write_to = s.num_rows_write_to;
	initialize_matrix_buffer(matrix_buffer, num_rows_write_to, i_values, incRowB);

	// initialize a column buffer
	// Dtype* buffer = (Dtype*)_mm_malloc(sizeof(Dtype)*ncol,32);
	i_j_pairs* pairs = s.pairs;
	// accumulate rows
	for(int i = 0; i < s.num_pairs; i++){
		i_j_pairs p = pairs[i];
		accumulate_rows(p, B, ncol, incRowB, buffer);
		add_row_to_rows(p, buffer, matrix_buffer, incRowB);
	}

	// scaling
	Dtype scaling_factor = s.value;
	if(incRowC % 8 == 0){
		scale_aligned_matrix(scaling_factor, matrix_buffer, num_rows_write_to, i_values, C, incRowC);
	}
	else{
		scale_unaligned_matrix(scaling_factor, matrix_buffer, num_rows_write_to, i_values, C, incRowC);
	}
}

void SparseMatrixMultiplication(int M, int N, int K,
			  SparseMatrix* A,
			  Dtype* B, int incRowB,
			  Dtype* C, int incRowC){
	assert(((unsigned long)B & 31) == 0);
	assert(incRowB % 8 ==0 );
	assert(M == getNumberOfRow(A));
	assert(K == getNumberOfCol(A));

	int rank = getNumberOfDistinctElement(A);
	Scaler* scalers = getScalers(A);
	for(int i = 0; i < rank; i++){
		Scaler s = scalers[i];
		if(s.value == 0.0){
			continue;
		}
		ScaleMatrixTo(s,
					B, K, N, incRowB,
					C, M, N, incRowC);
	}
}
