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

	int j = 0;
	int ncol_to_parralelize = ncol - ncol % 32;
	if(ncol_to_parralelize > 0){
	  __asm__ __volatile__
	  (
	  	"movq %0, %%r15 \n\t" // r15 correspond to row_1
	    "movq %1, %%r14 \n\t" // r14 correspond to row_2
	    "movq %2, %%r13 \n\t" // r13 correspond to row_3
	    "movq %3, %%r12 \n\t" // r12 correspond to row_4
	    "movq %4, %%r11 \n\t" // r11 correspond to row_4
	    "movq %5, %%r10 \n\t" // r10 correspond to row_4
	    "movq %6, %%r9 \n\t" // r9 correspond to row_4
	    "movq %7, %%r8 \n\t" // r8 correspond to row_4
	    "movq %8, %%rdi \n\t" // rdi stores the buffer address
	    "movq $0, %%rsi \n\t" // rsi counts the current offset
	    


	    "loop:"

	    // "movq %%rbx, %%r15 \n\t"
	    "vmovaps (%%r15, %%rsi, 4), %%ymm0 \n\t"
	    "vmovaps (%%r14, %%rsi, 4), %%ymm1 \n\t"
	    "vmovaps (%%r13, %%rsi, 4), %%ymm2 \n\t"
	    "vmovaps (%%r12, %%rsi, 4), %%ymm3 \n\t"
	    "vmovaps (%%r11, %%rsi, 4), %%ymm4 \n\t"
	    "vmovaps (%%r10, %%rsi, 4), %%ymm5 \n\t"
	    "vmovaps (%%r9, %%rsi, 4), %%ymm6 \n\t"
	    "vmovaps (%%r8, %%rsi, 4), %%ymm7 \n\t"
	    "vmovaps (%%rdi, %%rsi, 4), %%ymm8 \n\t"

	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm3, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm5, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm6, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm7, %%ymm0 \n\t"

	    "vaddps %%ymm0, %%ymm8, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, (%%rdi, %%rsi, 4) \n\t"
	    // "addq      $32,     %%r15    \n\t"  // B1_row += 8;


	    "vmovaps 32(%%r15, %%rsi, 4), %%ymm0 \n\t"
	    "vmovaps 32(%%r14, %%rsi, 4), %%ymm1 \n\t"
	    "vmovaps 32(%%r13, %%rsi, 4), %%ymm2 \n\t"
	    "vmovaps 32(%%r12, %%rsi, 4), %%ymm3 \n\t"
	    "vmovaps 32(%%r11, %%rsi, 4), %%ymm4 \n\t"
	    "vmovaps 32(%%r10, %%rsi, 4), %%ymm5 \n\t"
	    "vmovaps 32(%%r9, %%rsi, 4), %%ymm6 \n\t"
	    "vmovaps 32(%%r8, %%rsi, 4), %%ymm7 \n\t"
	    "vmovaps 32(%%rdi, %%rsi, 4), %%ymm8 \n\t"

	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm3, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm5, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm6, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm7, %%ymm0 \n\t"

	    "vaddps %%ymm0, %%ymm8, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, 32(%%rdi, %%rsi, 4) \n\t"


	    "vmovaps 64(%%r15, %%rsi, 4), %%ymm0 \n\t"
	    "vmovaps 64(%%r14, %%rsi, 4), %%ymm1 \n\t"
	    "vmovaps 64(%%r13, %%rsi, 4), %%ymm2 \n\t"
	    "vmovaps 64(%%r12, %%rsi, 4), %%ymm3 \n\t"
	    "vmovaps 64(%%r11, %%rsi, 4), %%ymm4 \n\t"
	    "vmovaps 64(%%r10, %%rsi, 4), %%ymm5 \n\t"
	    "vmovaps 64(%%r9, %%rsi, 4), %%ymm6 \n\t"
	    "vmovaps 64(%%r8, %%rsi, 4), %%ymm7 \n\t"
	    "vmovaps 64(%%rdi, %%rsi, 4), %%ymm8 \n\t"

	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm3, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm5, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm6, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm7, %%ymm0 \n\t"

	    "vaddps %%ymm0, %%ymm8, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, 64(%%rdi, %%rsi, 4) \n\t"



	    "vmovaps 96(%%r15, %%rsi, 4), %%ymm0 \n\t"
	    "vmovaps 96(%%r14, %%rsi, 4), %%ymm1 \n\t"
	    "vmovaps 96(%%r13, %%rsi, 4), %%ymm2 \n\t"
	    "vmovaps 96(%%r12, %%rsi, 4), %%ymm3 \n\t"
	    "vmovaps 96(%%r11, %%rsi, 4), %%ymm4 \n\t"
	    "vmovaps 96(%%r10, %%rsi, 4), %%ymm5 \n\t"
	    "vmovaps 96(%%r9, %%rsi, 4), %%ymm6 \n\t"
	    "vmovaps 96(%%r8, %%rsi, 4), %%ymm7 \n\t"
	    "vmovaps 96(%%rdi, %%rsi, 4), %%ymm8 \n\t"

	    "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm3, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm5, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm6, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm7, %%ymm0 \n\t"

	    "vaddps %%ymm0, %%ymm8, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, 96(%%rdi, %%rsi, 4) \n\t"


	    // "addq      $32,     %%r15    \n\t"  // B1_row += 8;
	    "addq      $32,     %%rsi \n\t"


	    "cmpq %%rsi, %%rax;"
	    "jg loop;"
	    : // no output
	    : "m" (B1_row),
	      "m" (B2_row), 
	      "m" (B3_row),
	      "m" (B4_row),
	      "m" (B5_row),
	      "m" (B6_row),
	      "m" (B7_row),
	      "m" (B8_row),
	      "m" (buffer),
	      "a" (ncol_to_parralelize)
	      // "d" (SOME_VALUE)
	    : "rdi", "rsi","r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8"
	  );
	}

	for(int j = ncol_to_parralelize; j < ncol; j+=8){
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
	for(int j = 0; j < ncol; j+=8){
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

void accumulate_rows(const i_j_pairs pairs, Dtype* B, int ncol, int incRowB, Dtype* buffer){
	int num_j = pairs.num_j_values;
	
	// js stores the row numbers
	int* js = pairs.j_values;
	// initialize a buffer
	__m256 zeros_ = _mm256_set1_ps(0);
	for(int i = 0; i < ncol; i+=8){
		_mm256_store_ps(&buffer[i], zeros_);
	}

	int i = 0;
	// unrolling factor of 8, each time, accumulate 8 rows	
	int remaining_rows = num_j % 8;
	int num_accumulated_rows = num_j - remaining_rows;
	for(; i < num_accumulated_rows; i+=8){
		accumulate_8_row(&js[i], B, ncol, incRowB, buffer);
	}

	// accumulate the other rows
	if(remaining_rows)
		accumulate_rows_small_number(remaining_rows, &js[i], B, ncol, incRowB, buffer);

}