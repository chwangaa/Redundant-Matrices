#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <sys/time.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

typedef float Dtype;
#define FLOAT

typedef struct i_j_pairs{
	int i_value;
	int num_of_pairs;
	int* j_values;
}i_j_pairs;

typedef struct Scaler{
	Dtype value;
	int num_i_value;
	i_j_pairs* pairs;
}Scaler;

typedef struct SparseMatrix{
	int rank;	// number of distinct values
	int col;	// number of columns
	int row;	// number of rows
	Scaler* scalers;
}SparseMatrix;



SparseMatrix* init_SparseMatrix(const char* file_name);

void SparseMatrixMultiplication(int M, int N, int K,
			  SparseMatrix* A,
			  Dtype* B, int incRowB,
			  Dtype* C, int incRowC);

void accumulate_rows(const i_j_pairs pairs,
					 Dtype* B, int ncol, int incRowB,
					 Dtype* buffer);

#endif