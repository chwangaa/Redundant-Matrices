#include <emmintrin.h>
#include <immintrin.h>
#include <assert.h>
#include "sparse_matrix.h"


static void accumulate_8_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	int r7 = js[6];
	int r8 = js[7];
	Dtype* B1_row = &B[r1*incRowB];
	Dtype* B2_row = &B[r2*incRowB];
	Dtype* B3_row = &B[r3*incRowB];
	Dtype* B4_row = &B[r4*incRowB];
    Dtype* B5_row = &B[r5*incRowB];
	Dtype* B6_row = &B[r6*incRowB];
	Dtype* B7_row = &B[r7*incRowB];
	Dtype* B8_row = &B[r8*incRowB];		


#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		const __m256 r1 = _mm256_load_ps(B1_row+j);
		const __m256 r2 = _mm256_load_ps(B2_row+j);
		const __m256 r3 = _mm256_load_ps(B3_row+j);
		const __m256 r4 = _mm256_load_ps(B4_row+j);
		const __m256 r5 = _mm256_load_ps(B5_row+j);
		const __m256 r6 = _mm256_load_ps(B6_row+j);
		const __m256 r7 = _mm256_load_ps(B7_row+j);
		const __m256 r8 = _mm256_load_ps(B8_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		#pragma offload
		temp += r1 + r2 + r3 + r4 + r5 + r6 + r7 + r8;			
		_mm256_store_ps(&buffer[j], temp);
	}

}

static void accumulate_7_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	int r7 = js[6];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	register Dtype* B3_row = &B[r3*incRowB];
	register Dtype* B4_row = &B[r4*incRowB];
	register Dtype* B5_row = &B[r5*incRowB];
	register Dtype* B6_row = &B[r6*incRowB];
	register Dtype* B7_row = &B[r7*incRowB];
	
#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);
		__m256 r6 = _mm256_load_ps(B6_row+j);
		__m256 r7 = _mm256_load_ps(B7_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2 + r3 + r4 + r5 + r6 + r7;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_6_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	register Dtype* B3_row = &B[r3*incRowB];
	register Dtype* B4_row = &B[r4*incRowB];
	register Dtype* B5_row = &B[r5*incRowB];
	register Dtype* B6_row = &B[r6*incRowB];
	
#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);
		__m256 r6 = _mm256_load_ps(B6_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2 + r3 + r4 + r5 + r6;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_5_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	register Dtype* B3_row = &B[r3*incRowB];
	register Dtype* B4_row = &B[r4*incRowB];
	register Dtype* B5_row = &B[r5*incRowB];
	
	#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2 + r3 + r4 + r5;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_4_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	register Dtype* B3_row = &B[r3*incRowB];
	register Dtype* B4_row = &B[r4*incRowB];
	
	#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2 + r3 + r4;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_3_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	register Dtype* B3_row = &B[r3*incRowB];
	
	#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);

		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2 + r3;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_2_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	register Dtype* B1_row = &B[r1*incRowB];
	register Dtype* B2_row = &B[r2*incRowB];
	#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1 + r2;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_1_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	register Dtype* B1_row = &B[r1*incRowB];
	#pragma GCC ivdep
	for(int j = 0; j < ncol; j+=8){
		// _mm_prefetch(B1_row+j+8, _MM_HINT_T0);
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 temp = _mm256_load_ps(&buffer[j]);
		temp += r1;			
		_mm256_store_ps(&buffer[j], temp);
	}
}

static void accumulate_rows_small_number(const int num_rows, const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	switch(num_rows){
		case 7:
			accumulate_7_row(js, B, ncol, incRowB, buffer);
			break;
		case 6:
			accumulate_6_row(js, B, ncol, incRowB, buffer);
			break;
		case 5:
			accumulate_5_row(js, B, ncol, incRowB, buffer);
			break;
		case 4:
			accumulate_4_row(js, B, ncol, incRowB, buffer);
			break;
		case 3:
			accumulate_3_row(js, B, ncol, incRowB, buffer);
			break;
		case 2:
			accumulate_2_row(js, B, ncol, incRowB, buffer);
			break;
		case 1:
			accumulate_1_row(js, B, ncol, incRowB, buffer);
			break;
		default:
			assert(0);
	}
}


void scale_and_copy_to_row(int n, Dtype scaler, Dtype* A, Dtype* B){
	__m256 scalar_ = _mm256_set1_ps(scaler);
	#pragma GCC ivdep
	for(int i = 0; i < n; i+=8){
		_mm_prefetch(B+i, _MM_HINT_NTA);
		__m256 As = _mm256_load_ps(A+i);
		__m256 Bs = _mm256_load_ps(B+i);
		__m256 Ms = _mm256_fmadd_ps(As, scalar_, Bs);
		_mm256_store_ps(B+i, Ms);
	}
	return;
}

void scale_and_copy_to_2row(int n, Dtype scaler, Dtype* buffer, Dtype* B1, Dtype* B2){
	__m256 scalar_ = _mm256_set1_ps(scaler);
	for(int i = 0; i < n; i+=8){
		// fprintf(stderr, "%d ", i);
		__m256 As = _mm256_load_ps(buffer+i);
		__m256 B1s = _mm256_load_ps(B1+i);
		__m256 B2s = _mm256_load_ps(B2+i);
		
		__m256 multiplied = As * scaler;
		__m256 B1s_updated = B1s + multiplied;
		__m256 B2s_updated = B2s + multiplied;

		_mm256_store_ps(B1+i, B1s_updated);
		_mm256_store_ps(B2+i, B2s_updated);
	}
	return;	
}

void accumulate_rows_to_destination(const i_j_pairs pairs, Dtype* B, int ncol, int incRowB, Dtype* buffer, Dtype* C, Dtype scaling_factor){
	int num_j = pairs.num_j_values;
	
	// js stores the row numbers
	int* js = pairs.j_values;
	// initialize a buffer
	__m256 zero = _mm256_set1_ps(0);

	int num_i = pairs.num_i_values;

	int* is = pairs.i_values;
	
	for(int i = 0; i < ncol; i+=8){
		_mm256_store_ps(buffer+i, zero);
	}
	// unrolling factor of 8, each time, accumulate 8 rows	
	int remaining_rows = num_j % 8;
	int num_accumulated_rows = num_j - remaining_rows;

	int i = 0;
	for(; i < num_accumulated_rows; i+=8){
		accumulate_8_row(&js[i], B, ncol, incRowB, buffer);
	}

	// accumulate the other rows
	if(remaining_rows)
		accumulate_rows_small_number(remaining_rows, &js[i], B, ncol, incRowB, buffer);

	// fprintf(stderr, "switching on %d \n", num_i);
	switch(num_i){
		case 1:
			scale_and_copy_to_row(incRowB, scaling_factor, buffer, &C[is[0]*incRowB]);
			break;
		case 2:
			// fprintf(stderr, "the rows are %d %d \n", is[0], is[1]);
			scale_and_copy_to_2row(incRowB, scaling_factor, buffer, &C[is[0]*incRowB], &C[is[1]*incRowB]);
			break;
		case 0:
			assert(0);
			break;
		default:
			// fprintf(stderr, "default called \n");
			for(int i = 0; i < num_i; i++){
				scale_and_copy_to_row(incRowB, scaling_factor, buffer, &C[is[i]*incRowB]);
			}
		}
}