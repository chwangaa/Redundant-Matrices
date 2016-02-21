#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"
#include <assert.h>
#include <immintrin.h>
#include "sparse_util.h"

/*
This is the test case for multiplying
[[1,1,1,1,3,3,3,3],
 [2,2,2,2,2,2,2,2],
 [3,3,3,3,3,3,3,3],
 [1,1,1,1,2,2,2,2]]
by
[[1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1],
 [1,1,1,1,1,1,1,1]]
The answer should be
[[16,16,16,16,16,16,16,16],
 [16,16,16,16,16,16,16,16],
 [24,24,24,24,24,24,24,24],
 [12,12,12,12,12,12,12,12]]
*/

void test6(){
	SparseMatrix* matrix = init_SparseMatrix("test1");
	assert(matrix);
	int M = 4;
	int N = 8;
	int K = 8;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);


	for(int i = 0; i < N*K; i++){
		B[i] = 1;
	}

	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
		}
	}

	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);

	Dtype correct[4*8] = {16,16,16,16,16,16,16,16,
					 		16,16,16,16,16,16,16,16,
					 		24,24,24,24,24,24,24,24,
					 		12,12,12,12,12,12,12,12};

	int num_false = 0;
	for(int i = 0; i < M*N; i++){
		if(correct[i] != C[i]){
			num_false ++;
		}
	}
	_mm_free(B);
	_mm_free(C);

	if(num_false == 0){
		fprintf(stderr, "TEST 1 PASSES \n");
	}
	else{
		fprintf(stderr, "TEST 1 FAILS \n");
	}
}

int main(int argc, char** argv){
	test6();
}