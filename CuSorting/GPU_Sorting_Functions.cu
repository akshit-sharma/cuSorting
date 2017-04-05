#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

__global__ void odd_even_sort_int(int * d_int, size_t maxLimit) {
	size_t arrayIndex;
	int t_int;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;
	
	arrayIndex = arrayIndex * 2;

	if (arrayIndex + 1 < maxLimit) {
		if (d_int[arrayIndex] > d_int[arrayIndex + 1])
		{
			SWAP(t_int, arrayIndex, arrayIndex + 1, d_int);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_int[arrayIndex] > d_int[arrayIndex + 1])
			{
				SWAP(t_int, arrayIndex, arrayIndex + 1, d_int);
			}
		}
		__syncthreads();
	}
}


__global__ void odd_even_sort_llong(long long * d_llong, size_t maxLimit)
{
	//Function body

}

__global__ void odd_even_sort_string(std::string * d_string, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_int(int * d_int, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_llong(long long * d_llong, size_t maxLimit)
{
	//Function body

}

__global__ void shellsort_string(std::string * d_string, size_t maxLimit)
{
	//Function body

}


__global__ void quicksort_int(int * d_int, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_llong(long long * d_llong, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_string(std::string * d_string, size_t maxLimit)
{
	//Function body

}
