#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "sparse_matrix.h"

static void readInNewPair(FILE* fin, i_j_pairs* pair){
	assert(fin != NULL);
	int i_value;
	int num_of_pairs;
	fscanf(fin, "%d %d", &i_value, &num_of_pairs);
	pair->i_value = i_value;
	pair->num_of_pairs = num_of_pairs;
	int* j_values = (int*)malloc(sizeof(int)*num_of_pairs);
	
	for(int i = 0; i < num_of_pairs; i++){
		int temp;
		fscanf(fin, "%d", &temp);
		j_values[i] = temp;
	}
	pair->j_values = j_values;
}

static void readInNewScaler(FILE* fin, Scaler* new_s){
	assert(fin != NULL);
	Dtype scaler_value;
	int num_i_value;
	fscanf(fin, "%f %d", &scaler_value, &num_i_value);

	i_j_pairs* pairs = (i_j_pairs*)malloc(sizeof(i_j_pairs)*num_i_value);
	for(int i = 0; i < num_i_value; i++){
		readInNewPair(fin, &pairs[i]);
	}
	new_s->pairs = pairs;
	new_s->value = scaler_value;
	// fprintf(stderr, "the scaler read is %f \n", scaler_value);
	new_s->num_i_value = num_i_value;
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

void scaleRow(int n, Dtype scaler, Dtype* A, const Dtype* B){
	__m256 scalar_ = _mm256_set1_ps(scaler);
	for(int i = 0; i < n; i+=8){
		__m256 As = _mm256_load_ps(A+i);
		__m256 Bs = _mm256_load_ps(B+i);
		__m256 Ms = _mm256_mul_ps(As, scalar_);
		Ms += Bs;
		_mm256_store_ps(B+i, Ms);
	}
	return;
}

void ScaleMatrixTo(Scaler s,
				   Dtype* B, int nrow, int ncol, int incRowB,
				   Dtype* C, int M, int N, int incRowC){

	
	int number_of_i = s.num_i_value;
	i_j_pairs* pairs = s.pairs;
	Dtype scaling_factor = s.value;
	Dtype* buffer = (Dtype*)_mm_malloc(sizeof(Dtype)*ncol,32);
	for(int i = 0; i < number_of_i; i++){
		i_j_pairs p = pairs[i];
		int destination_row_number = p.i_value;
		Dtype* destination_row = &C[destination_row_number*incRowC];
		accumulate_rows(p, B, ncol, incRowB, buffer);
		scaleRow(ncol, scaling_factor, buffer, destination_row);
	}
	_mm_free(buffer);
}

void SparseMatrixMultiplication(int M, int N, int K,
			  SparseMatrix* A,
			  Dtype* B, int incRowB,
			  Dtype* C, int incRowC){
	assert(((unsigned long)B & 31) == 0);
	assert(M == getNumberOfRow(A));
	assert(K == getNumberOfCol(A));

	int rank = getNumberOfDistinctElement(A);
	Scaler* scalers = getScalers(A);
	for(int i = 0; i < rank; i++){
		Scaler s = scalers[i];
		if(s.value < 0.0001 && s.value > -0.0001){
			continue;
		} 
		ScaleMatrixTo(s,
					B, K, N, incRowB,
					C, M, N, incRowC);
	}
}
