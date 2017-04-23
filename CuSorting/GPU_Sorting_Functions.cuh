
#include <cuda_runtime.h>

#include "cuRDStruct.h"
#include "cuSDStruct.h"

#define gpuErrchk(ans) { gpuAssert((ans), __FILE__, __LINE__); }
inline void gpuAssert(cudaError_t code, const char *file, int line, bool abort = true)
{
	if (code != cudaSuccess)
	{
		fprintf(stderr, "GPUassert: %s \n %s %d\n", cudaGetErrorString(code), file, line);
		if (abort) exit(code);
	}
}

__global__ void bitonic_sort_int_initMax(int *dev_values);
__global__ void bitonic_sort_int(int *dev_values, int j, int k);

__global__ void bitonic_sort_llong_initMax(long long *dev_values);
__global__ void bitonic_sort_llong(long long *dev_values, int j, int k);

__global__ void odd_even_sort_int(int * d_int, size_t maxLimit);
__global__ void odd_even_sort_llong(long long * d_llong, size_t maxLimit);

__global__ void quicksort_int(int *data, size_t left, size_t right, size_t depth);
__global__ void quicksort_llong(long long * data, size_t left, size_t right, size_t depth);
