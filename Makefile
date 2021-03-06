SPARSE_INC = -I$(HOME)/Documents/codings/

TEST_CC = gcc -std=c99 -O3 -g $(SPARSE_INC) $^ -o $@ -lm -mavx

accumulate_row.o: accumulate_row.c
	gcc -std=c99 -O3 -msse -mavx -c -o $@ $< -lm

sparse.o: sparse_matrix.c sparse_matrix.h
	gcc -std=c99 -w -O3 -msse -mavx -c -o $@ $< -lm

sparse.s: sparse_matrix.c sparse_matrix.h
	gcc -std=c99 -msse -mavx -S sparse_matrix.c

sparse_test: sparse.o accumulate_row.o sparse_test1.c
	gcc -std=c99 -msse -mavx sparse.o accumulate_row.o sparse_test1.c -o build/sparse_test

benchmark_sparse: accumulate_row.o sparse.o benchmark_sparse.c
	gcc -std=c99 -O3 -msse -mavx sparse.o accumulate_row.o benchmark_sparse.c -o build/benchmark_sparse


test: sparse_test
	./build/sparse_test

benchmark: benchmark_sparse
	./build/benchmark_sparse