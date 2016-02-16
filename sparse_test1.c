#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"
#include <assert.h>
#include <immintrin.h>
#include "sparse_util.h"

void test3(){
	SparseMatrix* matrix = init_SparseMatrix("test_inputs/sparse_matrix_test2.txt");
	assert(matrix);
	int M = 4;
	int N = 8;
	int K = 8;
	int incRowB = N;
	int incRowC = N;
	// Dtype* B = (Dtype*)malloc(sizeof(Dtype)*K*N);
	// Dtype* C = (Dtype*)malloc(sizeof(Dtype)*M*N);
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);

	for(int i = 0; i < 64; i++){
		B[i] = 1;
	}

	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
		}
	}

	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	
	Dtype correct[32] = {8,8,8,8,8,8,8,8,
					     8,8,8,8,8,8,8,8,
						 20,20,20,20,20,20,20,20,
						 14,14,14,14,14,14,14,14};

	for(int i = 0; i < 32; i++){
		// fprintf(stderr, "%f \n", C[i]);
		assert(correct[i] == C[i]);
	}
	_mm_free(B);
	_mm_free(C);
	printf("test 3 passes \n");
}

void test4(){
	SparseMatrix* matrix = init_SparseMatrix("test_inputs/sparse_matrix_test3.txt");
	assert(matrix);
	int M = 8;
	int N = 8;
	int K = 10;
	int incRowB = N;
	int incRowC = N;
	// Dtype* B = (Dtype*)malloc(sizeof(Dtype)*K*N);
	// Dtype* C = (Dtype*)malloc(sizeof(Dtype)*M*N);
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	int index = 0;
	for(int i = 0; i < K; i++){
		for(int j = 0; j < N; j++)
			B[i*N+j] = index++;
	}

	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
		}
	}

	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			// fprintf(stderr, "%.2f ", C[i*N+j]);
			assert((i+1)*360+j*10*(i+1) == C[i*N+j]);
		}
	}

	index = 0;
	for(int i = 0; i < K; i++){
		for(int j = 0; j < N; j++)
			assert(B[i*N+j] == index++);
	}

	_mm_free(B);
	_mm_free(C);
	printf("test 4 passes \n");
}

void test5(){
	SparseMatrix* matrix = init_SparseMatrix("test_inputs/sparse_matrix_test4.txt");
	assert(matrix);
	int M = 10;
	int N = 8;
	int K = 10;
	int incRowB = N;
	int incRowC = N;
	// Dtype* B = (Dtype*)malloc(sizeof(Dtype)*K*N);
	// Dtype* C = (Dtype*)malloc(sizeof(Dtype)*M*N);
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
	
	// Dtype correct[32] = {8,8,8,8,8,8,8,8,
					     // 8,8,8,8,8,8,8,8,
						 // 20,20,20,20,20,20,20,20,
						 // 14,14,14,14,14,14,14,14};

	for(int i = 0; i < M; i++){
		// fprintf(stderr, "%.2f \n", C[i]);
		for(int j = 0; j < N; j++)
			// fprintf(stderr, "%.2f \n", C[i*N+j]);
			assert(450+i*10 == C[i*N+j]);
	}
	_mm_free(B);
	_mm_free(C);
	printf("test 5 passes \n");
}

int main(int argc, char** argv){
	test3();
	test4();
	test5();
}