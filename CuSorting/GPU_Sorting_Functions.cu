#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

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

	/*
	printf("paper id %d \n classPtr is %llu threadIdx is %llu \n",
		single_PaperIdWrapper->paper_id,
		single_PaperIdWrapper->classPtr,
		threadIndex
	);
	*/

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
//			atomicExch(&d_PaperIdWrapper[arrayIndex + 1].paper_id, atomicExch(&d_PaperIdWrapper[arrayIndex].paper_id, d_PaperIdWrapper[arrayIndex + 1].paper_id));
//			atomicExch(&d_PaperIdWrapper[arrayIndex + 1].classPtr, atomicExch(&d_PaperIdWrapper[arrayIndex].classPtr, d_PaperIdWrapper[arrayIndex + 1].classPtr));
			temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
//			temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
			d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
//			d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
			d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
//			d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
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
//				atomicExch(&d_PaperIdWrapper[arrayIndex + 1].paper_id, atomicExch(&d_PaperIdWrapper[arrayIndex].paper_id, d_PaperIdWrapper[arrayIndex + 1].paper_id));
//				atomicExch(&d_PaperIdWrapper[arrayIndex + 1].classPtr, atomicExch(&d_PaperIdWrapper[arrayIndex].classPtr, d_PaperIdWrapper[arrayIndex + 1].classPtr));
				temp.paper_id = d_PaperIdWrapper[arrayIndex].paper_id;
//				temp.classPtr = d_PaperIdWrapper[arrayIndex].classPtr;
				d_PaperIdWrapper[arrayIndex].paper_id = d_PaperIdWrapper[arrayIndex + 1].paper_id;
//				d_PaperIdWrapper[arrayIndex].classPtr = d_PaperIdWrapper[arrayIndex + 1].classPtr;
				d_PaperIdWrapper[arrayIndex + 1].paper_id = temp.paper_id;
//				d_PaperIdWrapper[arrayIndex + 1].classPtr = temp.classPtr;
				//				printf("after odd swap \n");
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex], threadIndex);
				//				printPaperIdCombinationScheme(&d_PaperIdWrapper[arrayIndex + 1], threadIndex);
			}
		}
		__syncthreads();
	}

}


__global__ void odd_even_sort_scheme_paperid(PaperIdWrapper_Scheme * d_PaperIdWrapper, size_t maxLimit, int offset)
{
	size_t threadIndex;
	size_t arrayIndex;
	size_t internal_max;
	PaperIdWrapper_Scheme temp;

	threadIndex = threadIdx.x + blockIdx.x*blockDim.x;
	threadIndex += offset;

	internal_max = (blockIdx.x + 1) * blockDim.x;
	internal_max += offset;

	arrayIndex = threadIndex * 2;

	if (arrayIndex + 1 < maxLimit) {
		if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
		{
			//			printf("SWAP 1 called by %d on %d & %d \n", threadIndex, arrayIndex, arrayIndex + 1);
			SWAP_FOR_GPU_SPEC(d_PaperIdWrapper, paper_id, temp.paper_id, arrayIndex, arrayIndex + 1);
			SWAP_FOR_GPU_SPEC(d_PaperIdWrapper, classPtr, temp.classPtr, arrayIndex, arrayIndex + 1);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_PaperIdWrapper[arrayIndex].paper_id > d_PaperIdWrapper[arrayIndex + 1].paper_id)
			{
				//			printf("SWAP 2 called by %d on %d & %d \n", threadIndex, arrayIndex, arrayIndex + 1);
				SWAP_FOR_GPU_SPEC(d_PaperIdWrapper, paper_id, temp.paper_id, arrayIndex, arrayIndex + 1);
				SWAP_FOR_GPU_SPEC(d_PaperIdWrapper, classPtr, temp.classPtr, arrayIndex, arrayIndex + 1);
			}
		}
		__syncthreads();
	}
}

__global__ void odd_even_sort_scheme_paperid_separate(int * d_paper_id, SchemeDataStructure ** d_classPtr, size_t maxLimit, int offset) {
	size_t threadIndex;
	size_t arrayIndex;
	size_t internal_max;
	int t_int;
	SchemeDataStructure * t_classPtr;

	threadIndex = threadIdx.x + blockIdx.x*blockDim.x;
	threadIndex += offset;

	internal_max = (blockIdx.x + 1) * blockDim.x;
	internal_max += offset;

	arrayIndex = threadIndex * 2;

	if (arrayIndex + 1 < maxLimit) {
		if (d_paper_id[arrayIndex] > d_paper_id[arrayIndex + 1])
		{
			//			printf("SWAP 1 called by %d on %d & %d \n", threadIndex, arrayIndex, arrayIndex + 1);
			SWAP_FOR_GPU(d_paper_id, t_int, arrayIndex, arrayIndex + 1);
			SWAP_FOR_GPU(d_classPtr, t_classPtr, arrayIndex, arrayIndex + 1);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_paper_id[arrayIndex] > d_paper_id[arrayIndex + 1])
			{
				//			printf("SWAP 2 called by %d on %d & %d \n", threadIndex, arrayIndex, arrayIndex + 1);
				SWAP_FOR_GPU(d_paper_id, t_int, arrayIndex, arrayIndex + 1);
				SWAP_FOR_GPU(d_classPtr, t_classPtr, arrayIndex, arrayIndex + 1);
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

