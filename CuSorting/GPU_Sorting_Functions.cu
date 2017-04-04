#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"

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

__device__ __host__ void printPaperIdCombinationScheme(PaperIdWrapper_Scheme * single_PaperIdWrapper, size_t threadIndex) {
	int paperId;
	SchemeDataStructure * schemeDataStructure;

	paperId = single_PaperIdWrapper->paper_id;
	schemeDataStructure = single_PaperIdWrapper->classPtr;


	printf("paper id %d \n classPtr is %llu threadIdx is %llu \n",
		single_PaperIdWrapper->paper_id,
		single_PaperIdWrapper->classPtr,
		threadIndex
	);

}


__global__ void odd_even_sort_scheme_paperid_swap_edges_only(PaperIdWrapper_Scheme * d_PaperIdWrapper, size_t maxLimit)
{
	size_t threadIndex;
	size_t arrayIndex;
	PaperIdWrapper_Scheme temp;
	size_t internal_max;

	threadIndex = (threadIdx.x + 1) * blockDim.x;

	arrayIndex = threadIndex * 2;

	//printf("kernel called \n");

	if (arrayIndex + 1 < maxLimit) {
		if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
		{
			//			printf("\nbefore even swap from gpu \n");
			//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
			//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex+1], threadIndex);
			temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
			temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
			d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
			d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
			d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
			d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
			//			printf("\nafter even swap from gpu \n");
			//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
			//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
			{
				//				printf("before odd swap \n");
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
				temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
				temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
				d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
				d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
				d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
				d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
				//				printf("after odd swap \n");
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
			}
		}
		__syncthreads();
	}

}


__global__ void odd_even_sort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper, size_t maxLimit)
{
	size_t threadIndex;
	size_t arrayIndex;
	PaperIdWrapper_Scheme temp;
	size_t internal_max;

	threadIndex = threadIdx.x + blockIdx.x*blockDim.x;
	
	internal_max = (blockIdx.x + 1) * blockDim.x;

	arrayIndex = threadIndex * 2;

	//printf("kernel called \n");

	if (arrayIndex+1 < maxLimit && arrayIndex+1 < internal_max) {
		if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
		{
//			printf("\nbefore even swap from gpu \n");
//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex+1], threadIndex);
			temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
			temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
			d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
			d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
			d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
			d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
//			printf("\nafter even swap from gpu \n");
//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
//			printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex+1 < maxLimit && arrayIndex + 1 < internal_max) {
			if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
			{
//				printf("before odd swap \n");
//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
				temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
				temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
				d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
				d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
				d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
				d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
//				printf("after odd swap \n");
//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
			}
		}
		__syncthreads();
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

