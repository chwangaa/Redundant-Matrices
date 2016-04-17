#include <stdio.h>
#include <stdlib.h>
#include "sparse_matrix.h"
#include <assert.h>
#include <malloc.h>
#include <immintrin.h>
#include "sparse_util.h"

void *aligned_malloc_(int ALIGN, long size) {
    void *mem = malloc(size+ALIGN+sizeof(void*));
    void **ptr = (void**)((uintptr_t)(mem+ALIGN+sizeof(void*)) & ~(ALIGN-1));
    ptr[-1] = mem;
    return ptr;
}

void test_german_conv2(){
	SparseMatrix* matrix = init_SparseMatrix("models/gtsrb/conv2_sparse");
	fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 150;
	int N = 400;
	int K = 1600;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
			
		}
	}

	for(int i = 0; i < K; i++){
		for(int j = 0; j < N; j++){
			B[i*incRowB+j] = 0;
		}
	}

	uint64_t start_time = timestamp_us();
	assert(((unsigned long)B & 31) == 0);
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	
}

void test_german_conv1(){
	SparseMatrix* matrix = init_SparseMatrix("models/gtsrb/conv1_sparse");
	// fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 100;
	int N = 2116;
	int K = 27;
	int incRowB = 2120;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*incRowB,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
			
		}
	}

	for(int i = 0; i < K; i++){
		for(int j = 0; j < N; j++){
			B[i*incRowB+j] = 0;
			
		}
	}


	uint64_t start_time = timestamp_us();
	assert(((unsigned long)B & 31) == 0);
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	
}

void test_german_conv3(){
	SparseMatrix* matrix = init_SparseMatrix("models/gtsrb/conv3_sparse");
	fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 250;
	int N = 64;
	int K = 1350;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
			
		}
	}

	uint64_t start_time = timestamp_us();
	assert(((unsigned long)B & 31) == 0);
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	
}


void test_cifar_conv1(){
	SparseMatrix* matrix = init_SparseMatrix("models/cifar/conv1_sparse_round2");
	// fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 16;
	int N = 1024;
	int K = 75;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	fprintf(stderr, "load the test input image \n");
	load_matrix("cifar_conv1_test_input.txt", K, N, B);
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;		
		}
	}

	uint64_t start_time = timestamp_us();
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	

}


void test_cifar_conv2(){
	SparseMatrix* matrix = init_SparseMatrix("models/cifar/conv2_sparse_round2");
	fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 20;
	int N = 256;
	int K = 400;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
			
		}
	}

	uint64_t start_time = timestamp_us();
	assert(((unsigned long)B & 31) == 0);
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	
}

void test_cifar_conv3(){
	SparseMatrix* matrix = init_SparseMatrix("models/cifar/conv3_sparse_round2");
	fprintf(stderr, "the rank of the matrix is %d \n", matrix->rank);
	assert(matrix);
	// return;
	// fprintf(stderr, "the number of distinct values are %d \n", matrix->rank);
	int M = 20;
	int N = 64;
	int K = 500;
	int incRowB = N;
	int incRowC = N;
	Dtype* B = (Dtype*)_mm_malloc(sizeof(Dtype)*K*N,32);
	Dtype* C = (Dtype*)_mm_malloc(sizeof(Dtype)*M*N,32);
	assert(((unsigned long)&B[4*incRowB] & 31) == 0);
	assert(((unsigned long)C & 31) == 0);
	assert(B);
	assert(C);
	
	for(int i = 0; i < M; i++){
		for(int j = 0; j < N; j++){
			C[i*incRowC+j] = 0;
			
		}
	}

	uint64_t start_time = timestamp_us();
	assert(((unsigned long)B & 31) == 0);
	SparseMatrixMultiplication(M, N, K, matrix, B, incRowB, C, incRowC);	
	uint64_t end_time = timestamp_us();
	double m_second = (double)(end_time-start_time)/1000.0;
	fprintf(stderr, "time elapsed is %lf \n", m_second);	
}

int main(int argc, char** argv){
	test_german_conv1();
}