#ifndef SPARSE_MATRIX_UTIL_H
#define SPARSE_MATRIX_UTIL_H
static inline uint64_t timestamp_us() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  return 1000000L * tv.tv_sec + tv.tv_usec;
}

static inline void load_matrix(const char* file_name, int M, int N, float* matrix){
	FILE* fin = fopen(file_name, "r");
	assert(fin != NULL);
	int M_;
	int N_;
	fscanf(fin, "%d %d", &M_, &N_);
	assert(M_ == M);
	assert(N_ == N);
	// fprintf(stderr, "the size of the matrix is %dx%d \n",M, N);
	
	for(int i = 0; i < M*N; i++){
		float temp;
		fscanf(fin, "%f", &temp);
		matrix[i] = temp;
	}
	fclose(fin);
}

#endif