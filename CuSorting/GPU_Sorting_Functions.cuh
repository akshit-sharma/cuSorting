
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

__global__ void odd_even_sort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit);
__global__ void odd_even_sort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit);
__global__ void odd_even_sort_scheme_paperid(int * d_PaperId, size_t maxLimit);
__global__ void odd_even_sort_results_paperid(int * d_int, size_t maxLimit);
__global__ void odd_even_sort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit);
__global__ void odd_even_sort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit);

__global__ void shellsort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit);
__global__ void shellsort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit);
__global__ void shellsort_scheme_paperid(int * d_PaperId, size_t maxLimit);
__global__ void shellsort_results_paperid(int * d_int, size_t maxLimit);
__global__ void shellsort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit);
__global__ void shellsort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit);

__global__ void quicksort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit);
__global__ void quicksort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit);
__global__ void quicksort_scheme_paperid(int * d_PaperId, size_t maxLimit);
__global__ void quicksort_results_paperid(int * d_int, size_t maxLimit);
__global__ void quicksort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit);
__global__ void quicksort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit);
