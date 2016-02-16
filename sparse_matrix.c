#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "sparse_matrix.h"
#include <emmintrin.h>
#include <immintrin.h>

#define ROW_8

#if defined(ROW_8)
	#define accumulateRows_Float accumulateRows
#elif defined(ROW_4)
	#define accumulateRows_Float_4 accumulateRows
#endif

typedef float v4sf __attribute__ ((vector_size (16)));
// typedef float v8sf __attribute__ ((vector_size (32)));
typedef int v4si __attribute__ ((vector_size (16)));


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


void accumulateRows_Float(const i_j_pairs pairs, Dtype* B, int nrow, int ncol, int incRowB, Dtype* buffer){
	int num_j = pairs.num_of_pairs;
	
	// copy over the first row to the buffer
	int* js = pairs.j_values;
	// initialize a buffer
	for(int i = 0; i < ncol; i++){
		buffer[i] = 0;
	}

	int i = 0;
	int remaining_rows = num_j % 8;
	int num_accumulated_rows = num_j - remaining_rows;
	
	// unrolling factor of 8, each time, accumulate 8 rows	
	for(; i < num_accumulated_rows; i+=8){
		int r1 = js[i];
		int r2 = js[i+1];
		int r3 = js[i+2];
		int r4 = js[i+3];
		int r5 = js[i+4];
		int r6 = js[i+5];
		int r7 = js[i+6];
		int r8 = js[i+7];
		Dtype* B1_row = &B[r1*incRowB];
		Dtype* B2_row = &B[r2*incRowB];
		Dtype* B3_row = &B[r3*incRowB];
		Dtype* B4_row = &B[r4*incRowB];
	    Dtype* B5_row = &B[r5*incRowB];
		Dtype* B6_row = &B[r6*incRowB];
		Dtype* B7_row = &B[r7*incRowB];
		Dtype* B8_row = &B[r8*incRowB];		


		for(int j = 0; j < ncol; j+=8){
			__m256 r1 = _mm256_load_ps(B1_row+j);
			__m256 r2 = _mm256_load_ps(B2_row+j);
			__m256 r3 = _mm256_load_ps(B3_row+j);
			__m256 r4 = _mm256_load_ps(B4_row+j);
			__m256 r5 = _mm256_load_ps(B5_row+j);
			__m256 r6 = _mm256_load_ps(B6_row+j);
			__m256 r7 = _mm256_load_ps(B7_row+j);
			__m256 r8 = _mm256_load_ps(B8_row+j);

			__m256 temp = _mm256_load_ps(&buffer[j]);
			temp += r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8;
			__m256 result;
			_mm256_store_ps(&buffer[j], temp);
		}

	  // int STEP_SIZE = 8;
	  // __asm__ __volatile__
	  // (
	  // 	"movq %0, %%r15 \n\t" // r15 correspond to row_1
	  //   "movq %1, %%r14 \n\t" // r14 correspond to row_2
	  //   "movq %2, %%r13 \n\t" // r13 correspond to row_3
	  //   "movq %3, %%r12 \n\t" // r12 correspond to row_4
	  //   "movq %4, %%r11 \n\t" // r11 correspond to row_4
	  //   "movq %5, %%r10 \n\t" // r10 correspond to row_4
	  //   "movq %6, %%r9 \n\t" // r9 correspond to row_4
	  //   "movq %7, %%r8 \n\t" // r8 correspond to row_4
	  //   "loop:"
	  //   // "movq %%rbx, %%r15 \n\t"
	  //   "vmovaps (%%r15), %%ymm0 \n\t"
	  //   "vmovaps (%%r14), %%ymm1 \n\t"
	  //   "vmovaps (%%r13), %%ymm2 \n\t"
	  //   "vmovaps (%%r12), %%ymm3 \n\t"
	  //   "vmovaps (%%r11), %%ymm4 \n\t"
	  //   "vmovaps (%%r10), %%ymm5 \n\t"
	  //   "vmovaps (%%r9), %%ymm6 \n\t"
	  //   "vmovaps (%%r8), %%ymm7 \n\t"

	  //   "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	  //   "vmovaps (%%rdx), %%ymm1 \n\t"
	  //   "vaddps %%ymm2, %%ymm3, %%ymm2 \n\t"
	  //   "vaddps %%ymm4, %%ymm5, %%ymm4 \n\t"
	  //   "vaddps %%ymm6, %%ymm7, %%ymm6 \n\t"
	    
	  //   "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	  //   "vaddps %%ymm4, %%ymm6, %%ymm4 \n\t"
	    
	  //   "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	  //   "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    
	  //   "vmovaps %%ymm0, (%%rdx) \n\t"
	  //   "leaq (%%r15, %%rcx, 4), %%r15;"
	  //   "leaq (%%r14, %%rcx, 4), %%r14;"
	  //   "leaq (%%r13, %%rcx, 4), %%r13;"
	  //   "leaq (%%r12, %%rcx, 4), %%r12;"
	  //   "leaq (%%r11, %%rcx, 4), %%r11;"
	  //   "leaq (%%r10, %%rcx, 4), %%r10;"
	  //   "leaq (%%r9, %%rcx, 4), %%r9;"
	  //   "leaq (%%r8, %%rcx, 4), %%r8;"
	  //   "leaq (%%rdx, %%rcx, 4), %%rdx;"
	  //   "cmpq %%r15, %%rax;"
	  //   "jg loop;"
	  //   : // no output
	  //   : "m" (B1_row),
	  //     "m" (B2_row), 
	  //     "m" (B3_row),
	  //     "m" (B4_row),
	  //     "m" (B5_row),
	  //     "m" (B6_row),
	  //     "m" (B7_row),
	  //     "m" (B8_row),
	  //     "d" (buffer),
	  //     "a" (B1_row + ncol),
	  //     "c" (STEP_SIZE)
	  //   : "r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8"
	  // );
	}
		
	// deal with the rest of the rows
	if(i <= num_j - 4){
		int r1 = js[i];
		int r2 = js[i+1];
		int r3 = js[i+2];
		int r4 = js[i+3];
		register Dtype* B1_row = &B[r1*incRowB];
		register Dtype* B2_row = &B[r2*incRowB];
		register Dtype* B3_row = &B[r3*incRowB];
		register Dtype* B4_row = &B[r4*incRowB];
		for(int j = 0; j < ncol; j+=8){
			__m256 r1 = _mm256_load_ps(B1_row+j);
			__m256 r2 = _mm256_load_ps(B2_row+j);
			__m256 r3 = _mm256_load_ps(B3_row+j);
			__m256 r4 = _mm256_load_ps(B4_row+j);

			__m256 temp = _mm256_load_ps(&buffer[j]);
			temp += r1 + r2 + r3 + r4;			
			_mm256_store_ps(&buffer[j], temp);
		}
		i += 4;
	}
	for(; i < num_j; i++){
		int r = js[i];
		Dtype* B_row = &B[r*incRowB];
		for(int j = 0; j < ncol; j+=8){
			__m256 r_temp = _mm256_load_ps(&buffer[j]);
			r_temp += _mm256_load_ps(B_row+j);
			_mm256_store_ps(&buffer[j], r_temp);
		}
	}
}


void accumulateRows_Float_4(const i_j_pairs pairs, Dtype* B, int nrow, int ncol, int incRowB, Dtype* buffer){
	int num_j = pairs.num_of_pairs;
	
	// copy over the first row to the buffer
	int* js = pairs.j_values;
	// initialize a buffer
	for(int i = 0; i < ncol; i++){
		buffer[i] = 0;
	}

	int i = 0;
	int remaining_rows = num_j % 4;
	int num_accumulated_rows = num_j - remaining_rows;
	
	// unrolling factor of 8, each time, accumulate 8 rows	
	for(; i < num_accumulated_rows; i+=4){
		int r1 = js[i];
		int r2 = js[i+1];
		int r3 = js[i+2];
		int r4 = js[i+3];
		Dtype* B1_row = &B[r1*incRowB];
		Dtype* B2_row = &B[r2*incRowB];
		Dtype* B3_row = &B[r3*incRowB];
		Dtype* B4_row = &B[r4*incRowB];

/*
		for(int j = 0; j < ncol; j+=8){
			__m256 r1 = _mm256_load_ps(B1_row+j);
			__m256 r2 = _mm256_load_ps(B2_row+j);
			__m256 r3 = _mm256_load_ps(B3_row+j);
			__m256 r4 = _mm256_load_ps(B4_row+j);

			__m256 temp = _mm256_load_ps(&buffer[j]);
			temp += r1 + r2 + r3 + r4;
			_mm256_store_ps(&buffer[j], temp);
		}
*/
	  int STEP_SIZE = 8;
	  float* B1_row_limit = B1_row + ncol;
	  __asm__ __volatile__
	  (
	  	"movq %0, %%r15 \n\t" // r15 correspond to row_1
	    "movq %1, %%r14 \n\t" // r14 correspond to row_2
	    "movq %2, %%r13 \n\t" // r13 correspond to row_3
	    "movq %3, %%r12 \n\t" // r12 correspond to row_4
	    "movq %4, %%r11 \n\t" // r11 correspond to buffer
	    "movq %5, %%r10 \n\t" // r10 is the buffer_limit
	    
	    "loop_4:"
	    "vmovaps (%%r15), %%ymm0 \n\t"
	    "vmovaps (%%r14), %%ymm1 \n\t"
	    "vmovaps (%%r13), %%ymm2 \n\t"
	    "vmovaps (%%r12), %%ymm3 \n\t"

	    "leaq (%%r15, %%rcx, 4), %%r15;"
	    "leaq (%%r14, %%rcx, 4), %%r14;"
	    "leaq (%%r13, %%rcx, 4), %%r13;"
	    "leaq (%%r12, %%rcx, 4), %%r12;"

	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    "vmovaps (%%r11), %%ymm1 \n\t"
	    "vaddps %%ymm2, %%ymm3, %%ymm2 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, (%%r11) \n\t"
	    "leaq (%%r11, %%rcx, 4), %%r11;"
		
		"prefetcht0 0(%%r15)\n\t"
		"prefetcht0 0(%%r14)\n\t"
		"prefetcht0 0(%%r12)\n\t"
		"prefetcht0 0(%%r11)\n\t"

	    "cmpq %%r15, %%r10;"
	    "jg loop_4;"
	    : // no output
	    : "m" (B1_row),
	      "m" (B2_row), 
	      "m" (B3_row),
	      "m" (B4_row),
	      "m" (buffer),
	      "m" (B1_row_limit),
	      "c" (STEP_SIZE)
	    : "cc", "memory", "r15", "r14", "r13", "r12", "r11", "r10"
	  );	  

	}
		
	// deal with the rest of the rows
	for(; i < num_j; i++){
		int r = js[i];
		Dtype* B_row = &B[r*incRowB];
		for(int j = 0; j < ncol; j+=8){
			__m256 r_temp = _mm256_load_ps(&buffer[j]);
			r_temp += _mm256_load_ps(B_row+j);
			_mm256_store_ps(&buffer[j], r_temp);
		}
	}
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
		accumulateRows(p, B, nrow, ncol, incRowB, buffer);
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
		// fprintf(stderr, "start scaling \n");
		Scaler s = scalers[i];
		if(s.value < 0.0001 && s.value > -0.0001){
			continue;
		} 
		// fprintf(stderr, "entering scaler \n");
		ScaleMatrixTo(s,
					B, K, N, incRowB,
					C, M, N, incRowC);
		// fprintf(stderr, "return from scaling \n");
	}
	// fprintf(stderr, "return from whole thing \n");
}
