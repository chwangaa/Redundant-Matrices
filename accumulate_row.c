#include <emmintrin.h>
#include <immintrin.h>
#include <assert.h>
#include "sparse_matrix.h"


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

void accumulate_8_row(const int* js, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	int r7 = js[6];
	int r8 = js[7];
	Dtype* restrict B1_row = &B[r1*incRowB];
	Dtype* restrict B2_row = &B[r2*incRowB];
	Dtype* restrict B3_row = &B[r3*incRowB];
	Dtype* restrict B4_row = &B[r4*incRowB];
    Dtype* restrict B5_row = &B[r5*incRowB];
	Dtype* restrict B6_row = &B[r6*incRowB];
	Dtype* restrict B7_row = &B[r7*incRowB];
	Dtype* restrict B8_row = &B[r8*incRowB];		


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
}



void accumulate_7_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	int r7 = js[6];
	register Dtype* restrict B1_row = &B[r1*incRowB];
	register Dtype* restrict B2_row = &B[r2*incRowB];
	register Dtype* restrict B3_row = &B[r3*incRowB];
	register Dtype* restrict B4_row = &B[r4*incRowB];
	register Dtype* restrict B5_row = &B[r5*incRowB];
	register Dtype* restrict B6_row = &B[r6*incRowB];
	register Dtype* restrict B7_row = &B[r7*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);
		__m256 r6 = _mm256_load_ps(B6_row+j);
		__m256 r7 = _mm256_load_ps(B7_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2 + r3 + r4 + r5 + r6 + r7;
		
		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_6_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	int r6 = js[5];
	register Dtype* restrict B1_row = &B[r1*incRowB];
	register Dtype* restrict B2_row = &B[r2*incRowB];
	register Dtype* restrict B3_row = &B[r3*incRowB];
	register Dtype* restrict B4_row = &B[r4*incRowB];
	register Dtype* restrict B5_row = &B[r5*incRowB];
	register Dtype* restrict B6_row = &B[r6*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);
		__m256 r6 = _mm256_load_ps(B6_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2 + r3 + r4 + r5 + r6;
		
		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_5_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	int r5 = js[4];
	register Dtype* restrict B1_row = &B[r1*incRowB];
	register Dtype* restrict B2_row = &B[r2*incRowB];
	register Dtype* restrict B3_row = &B[r3*incRowB];
	register Dtype* restrict B4_row = &B[r4*incRowB];
	register Dtype* restrict B5_row = &B[r5*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 r5 = _mm256_load_ps(B5_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2 + r3 + r4 + r5;
		
		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_4_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	int r4 = js[3];
	register Dtype* restrict B1_row = &B[r1*incRowB];
	register Dtype* restrict B2_row = &B[r2*incRowB];
	register Dtype* restrict B3_row = &B[r3*incRowB];
	register Dtype* restrict B4_row = &B[r4*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 r4 = _mm256_load_ps(B4_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2 + r3 + r4;
		
		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_3_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	int r3 = js[2];
	register Dtype* restrict B1_row = &B[r1*incRowB];
	register Dtype* restrict B2_row = &B[r2*incRowB];
	register Dtype* restrict B3_row = &B[r3*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 r3 = _mm256_load_ps(B3_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2 + r3;
		
		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_2_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	int r2 = js[1];
	Dtype* restrict B1_row = &B[r1*incRowB];
	Dtype* restrict B2_row = &B[r2*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 r2 = _mm256_load_ps(B2_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);
		__m256 sum = r1 + r2;

		temp += _mm256_mul_ps(sum, scalar_);
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_1_row_and_scale_to(const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* restrict destination_row){
	int r1 = js[0];
	Dtype* restrict B1_row = &B[r1*incRowB];
	__m256 scalar_ = _mm256_set1_ps(scaling_factor);	
	for(int j = 0; j < ncol; j+=8){
		__m256 r1 = _mm256_load_ps(B1_row+j);
		__m256 temp = _mm256_load_ps(destination_row+j);			
		temp += _mm256_mul_ps(r1, scalar_);
		
		_mm256_store_ps(&destination_row[j], temp);
	}
}

void accumulate_afew_row_and_scale_to(const int num_rows, const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* destination_row){
	switch(num_rows){
		case 7:
			accumulate_7_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 6:
			accumulate_6_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 5:
			accumulate_5_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 4:
			accumulate_4_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 3:
			accumulate_3_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 2:
			accumulate_2_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		case 1:
			accumulate_1_row_and_scale_to(js, B, ncol, incRowB, scaling_factor, destination_row);
			break;
		default:
			assert(0);
	}
}

void accumulate_many_row_and_scale_to(const int num_rows, const int* js, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* destination_row){
	// initialize a buffer
	Dtype* buffer = (Dtype*)_mm_malloc(sizeof(Dtype)*ncol,32);

	for(int i = 0; i < ncol; i++){
		buffer[i] = 0;
	}

	int i = 0;
	// unrolling factor of 8, each time, accumulate 8 rows	
	int remaining_rows = num_rows % 8;
	int num_accumulated_rows = num_rows - remaining_rows;
	for(; i < num_accumulated_rows; i+=8){
		accumulate_8_row(&js[i], B, ncol, incRowB, buffer);
	}
	scaleRow(ncol, scaling_factor, buffer, destination_row);
	_mm_free(buffer);

	// accumulate the other rows
	if(remaining_rows)
		accumulate_afew_row_and_scale_to(remaining_rows, &js[i], B, ncol, incRowB, scaling_factor, destination_row);	
}

void accumulate_rows_and_scale_to(const i_j_pairs pairs, Dtype* B, int ncol, int incRowB, Dtype scaling_factor, Dtype* destination_row){
	int num_j = pairs.num_of_pairs;
	int* js = pairs.j_values;

	if(num_j >= 8){
		accumulate_many_row_and_scale_to(num_j, js, B, ncol, incRowB, scaling_factor, destination_row);
	}
	else{
		accumulate_afew_row_and_scale_to(num_j, js, B, ncol, incRowB, scaling_factor, destination_row);
	}	
}