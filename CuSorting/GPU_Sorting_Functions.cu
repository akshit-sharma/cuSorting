#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

__global__ void odd_even_sort_scheme_paperid(int * d_paper_id, size_t maxLimit) {
	size_t arrayIndex;
	int t_int;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;
	
	arrayIndex = arrayIndex * 2;

	if (arrayIndex + 1 < maxLimit) {
		if (d_paper_id[arrayIndex] > d_paper_id[arrayIndex + 1])
		{
			SWAP(t_int, arrayIndex, arrayIndex + 1, d_paper_id);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_paper_id[arrayIndex] > d_paper_id[arrayIndex + 1])
			{
				SWAP(t_int, arrayIndex, arrayIndex + 1, d_paper_id);
			}
		}
		__syncthreads();
	}
}


__global__ void odd_even_sort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void odd_even_sort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void odd_even_sort_results_paperid(int * d_int, size_t maxLimit)
{
	//Function body

}

__global__ void odd_even_sort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit)
{
	//Function body

}

__global__ void odd_even_sort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit)
{
	//Function body

}


__global__ void shellsort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_scheme_paperid(int * d_PaperId, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_results_paperid(int * d_int, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit)
{
	//Function body

}


__global__ void quicksort_scheme_instiname(std::string * d_institutionNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_scheme_subjname(std::string * d_subjectNameWrapper_Scheme, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_scheme_paperid(int * d_PaperId, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_results_paperid(int * d_int, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_results_rollnumber(long * d_results_rollnumberWrapper_Results, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_results_name(std::string * d_nameWrapper_Results, size_t maxLimit)
{
	//Function body

}



