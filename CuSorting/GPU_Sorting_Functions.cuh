
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

__global__ void odd_even_sort_int(int * d_int, size_t maxLimit);
__global__ void odd_even_sort_llong(long long * d_llong, size_t maxLimit);
__global__ void odd_even_sort_string(std::string * d_string, size_t maxLimit);

__global__ void shellsort_int(int * d_int, size_t maxLimit);
__global__ void shellsort_llong(long long * d_llong, size_t maxLimit);
__global__ void shellsort_string(std::string * d_string, size_t maxLimit);

__global__ void quicksort_int(unsigned int *data, int left, int right, int depth);
__global__ void quicksort_llong(long long * d_llong, size_t maxLimit);
__global__ void quicksort_string(std::string * d_string, size_t maxLimit);
