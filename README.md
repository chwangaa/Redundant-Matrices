#REDUNDANT MATRIX MULTIPLICATION

this library provide a faster approach to multiply matrices: A += B*C, where B has a lot of redundancies. For example, when the matrix is huge, but the number of distinct entries is very limited.


##TEST
run `make test`

##BENCHMARKING ON CNNs
`benchmark_sparse.c` include a few methods to benchmark different convolutional layers in Cifar and German

the example for 2nd cifar layer has with it a real input layer. The other examples simply uses all-zero-entry matrices.