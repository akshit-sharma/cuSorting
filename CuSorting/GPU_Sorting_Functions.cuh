
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

__global__ void checkArray(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme, size_t maxLimit);

__global__ void odd_even_sort_scheme_instiname(InstitutionNameWrapper_Scheme * d_institutionNameWrapper_Scheme);
__global__ void odd_even_sort_scheme_subjname(SubjectNameWrapper_Scheme * d_subjectNameWrapper_Scheme);
__global__ void odd_even_sort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme, size_t maxLimit);
__global__ void odd_even_sort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper_Results);
__global__ void odd_even_sort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results);
__global__ void odd_even_sort_results_name(NameWrapper_Results * d_nameWrapper_Results);

__global__ void shellsort_scheme_instiname(InstitutionNameWrapper_Scheme * d_institutionNameWrapper_Scheme);
__global__ void shellsort_scheme_subjname(SubjectNameWrapper_Scheme * d_subjectNameWrapper_Scheme);
__global__ void shellsort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme);
__global__ void shellsort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper_Results);
__global__ void shellsort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results);
__global__ void shellsort_results_name(NameWrapper_Results * d_nameWrapper_Results);

__global__ void quicksort_scheme_instiname(InstitutionNameWrapper_Scheme * d_institutionNameWrapper_Scheme);
__global__ void quicksort_scheme_subjname(SubjectNameWrapper_Scheme * d_subjectNameWrapper_Scheme);
__global__ void quicksort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme);
__global__ void quicksort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper_Results);
__global__ void quicksort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results);
__global__ void quicksort_results_name(NameWrapper_Results * d_nameWrapper_Results);
