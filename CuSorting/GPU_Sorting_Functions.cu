#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"

__global__ void checkArray(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme, size_t maxLimit)
{
	size_t threadIndex;

	threadIndex = threadIdx.x + blockIdx.x*blockDim.x;

	if (threadIndex + 1 < maxLimit) {
		if (d_PaperIdWrapper_Scheme[threadIndex].paper_id > d_PaperIdWrapper_Scheme[threadIndex+1].paper_id)
		{
			printf("Array not sorted \n %d is before %d \n\n",
				d_PaperIdWrapper_Scheme[threadIndex].paper_id,
				d_PaperIdWrapper_Scheme[threadIndex + 1].paper_id);
		}
	}

}

__global__ void odd_even_sort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper, size_t maxLimit)
{
	size_t threadIndex;
	size_t arrayIndex;
	PaperIdWrapper_Scheme temp;

	threadIndex = threadIdx.x + blockIdx.x*blockDim.x;

	arrayIndex = threadIndex * 2;
	if (arrayIndex+1 < maxLimit) {
		if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
		{
			temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
			temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
			d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
			d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
			d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
			d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
		}
		arrayIndex += 1;
		if (arrayIndex+1 < maxLimit) {
			if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
			{
				temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
				temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
				d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
				d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
				d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
				d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
			}
		}
	}

}

__global__ void odd_even_sort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper)
{
	// Function body

}

__global__ void odd_even_sort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results)
{
	// Function body

}

__global__ void shellsort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme)
{
	// Function body

}

__global__ void shellsort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper_Results)
{
	// Function body

}

__global__ void shellsort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results)
{
	// Function body

}

__global__ void quicksort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper_Scheme)
{
	// Function body

}

__global__ void quicksort_results_paperid(PaperIdWrapper_Results * d_PaperIdWrapper_Results)
{
	// Function body

}

__global__ void quicksort_results_rollnumber(RollNumberWrapper_Results * d_results_rollnumberWrapper_Results)
{
	// Function body

}

