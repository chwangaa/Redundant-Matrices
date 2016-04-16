#include <immintrin.h>
#include <emmintrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
typedef float v8sf __attribute__ ((vector_size (32)));

int main(){
	int ncol = 128;
	int SIZE = ncol;
	float* B1_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B2_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B3_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B4_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B5_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B6_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B7_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* B8_row = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	float* buffer = (float*)_mm_malloc(sizeof(float)*SIZE, 32);
	for(int i = 0; i < ncol; i++){
		B1_row[i] = i;
		B2_row[i] = i;
		B3_row[i] = i;
		B4_row[i] = i;
		B5_row[i] = i;
		B6_row[i] = i;
		B7_row[i] = i;
		B8_row[i] = i;
		buffer[i] = 0;
	}
	// fprintf(stderr, "values loaded \n");
	// __m256 c = {1,2,3,4,5,6,7,8};
	// __m256  = _mm256_load_ps(arr1);
	// int i = 8;
	// float* accum = (float*)_mm_malloc(sizeof(float)*16, 32);
	// int ARR_LEN = SIZE;
	// float* arr1_limit = arr1 + ARR_LEN;
	// int STEP_SIZE = 8;
	// float SOME_VALUE = 0.5;
	  // __asm__ __volatile__
	  // (
	  // 	"movq %0, %%r15 \n\t" // r15 correspond to row_1
	  //   "movq %1, %%r14 \n\t" // r14 correspond to row_2
	  //   "movq %2, %%r13 \n\t" // r13 correspond to row_3
	  //   "movq %3, %%r12 \n\t" // r12 correspond to row_4
	  //   "movq %4, %%r11 \n\t" // r11 correspond to buffer
	  //   "movq %5, %%r10 \n\t" // r10 is the buffer_limit
	  //   // "movq %%r15, %%rbx \n\t"
	  //   "loop:"
	  //   "vmovaps (%%r15), %%ymm0 \n\t"
	  //   "vmovaps (%%r14), %%ymm1 \n\t"
	  //   "vmovaps (%%r13), %%ymm2 \n\t"
	  //   "vmovaps (%%r12), %%ymm3 \n\t"
	  //   // "vmovaps (%%r11), %%ymm4 \n\t"
	  //   // "vmovaps (%%r10), %%ymm5 \n\t"
	  //   // "vmovaps (%%r9), %%ymm6 \n\t"
	  //   // "vmovaps (%%r8), %%ymm7 \n\t"

	  //   "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	  //   "vaddps %%ymm2, %%ymm3, %%ymm2 \n\t"
	  //   // "vaddps %%ymm4, %%ymm5, %%ymm4 \n\t"
	  //   // "vaddps %%ymm6, %%ymm7, %%ymm6 \n\t"
	    
	  //   "vmovaps (%%r11), %%ymm1 \n\t"
	  //   "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	  //   "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    
	  //   // "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	  //   // "vaddps %%ymm0, %%ymm1, %%ymm0 \n\t"
	    
	  //   "vmovaps %%ymm0, (%%r11) \n\t"
	  //   "leaq (%%r15, %%rcx, 4), %%r15;"
	  //   "leaq (%%r14, %%rcx, 4), %%r14;"
	  //   "leaq (%%r13, %%rcx, 4), %%r13;"
	  //   "leaq (%%r12, %%rcx, 4), %%r12;"
	  //   "leaq (%%r11, %%rcx, 4), %%r11;"
	  //   // "leaq (%%r10, %%rcx, 4), %%r10;"
	  //   // "leaq (%%r9, %%rcx, 4), %%r9;"
	  //   // "leaq (%%r8, %%rcx, 4), %%r8;"
	  //   // "leaq (%%rbx, %%rcx, 4), %%rbx;"
	  //   "cmpq %%r15, %%r10;"
	  //   "jg loop;"
	  //   : // no output
	  //   : "m" (arr1),
	  //     "m" (arr2), 
	  //     "m" (arr3),
	  //     "m" (arr4),
	  //     "m" (result),
	  //     "m" (arr1_limit),
	  //     "c" (STEP_SIZE)
	  //   : "cc", "memory", "r15", "r14", "r13", "r12", "r11", "r10"
	  // );

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
	    "vaddps %%ymm2, %%ymm3, %%ymm2 \n\t"
	    "vaddps %%ymm4, %%ymm5, %%ymm4 \n\t"
	    "vaddps %%ymm6, %%ymm7, %%ymm6 \n\t"
	    "vaddps %%ymm0, %%ymm2, %%ymm0 \n\t"
	    "vaddps %%ymm4, %%ymm6, %%ymm4 \n\t"
	    
	    "vaddps %%ymm0, %%ymm4, %%ymm0 \n\t"
	    "vaddps %%ymm0, %%ymm8, %%ymm0 \n\t"
	    
	    "vmovaps %%ymm0, (%%rdi, %%rsi, 4) \n\t"
	    // "addq      $32,     %%r15    \n\t"  // B1_row += 8;
	    "addq      $8,     %%rsi \n\t"
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
	      "a" (128)
	      // "d" (SOME_VALUE)
	    : "rdi", "rsi","r15", "r14", "r13", "r12", "r11", "r10", "r9", "r8"
	  );

	  for(int i = 0; i < ncol; i++){
	  	fprintf(stderr, "%.2f ", buffer[i]);
	  }
	// fprintf(stderr, "values loaded to vector \n");
	// v4si b = {5,6,7,8};
	// v4si c = a + b;
	// fprintf(stderr, "%.2f %.2f %.2f %.2f \n", accum[0], accum[1], accum[2], accum[3]);
	return 0;
    // return __builtin_mulv4si (tmp, c);
}