#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

__global__ void odd_even_sort_int_xtra(int * d_int, size_t maxLimit, size_t loop)
{
	size_t arrayIndex;
	size_t i, end;
	int t_int;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;

	arrayIndex = arrayIndex * 2;
	
	end = (arrayIndex * loop);

	for (i = loop; i < end; i+=2) {
		arrayIndex = i;
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
}

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
	size_t arrayIndex;
	int t_llong;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;

	arrayIndex = arrayIndex * 2;

	if (arrayIndex + 1 < maxLimit) {
		if (d_llong[arrayIndex] > d_llong[arrayIndex + 1])
		{
			SWAP(t_llong, arrayIndex, arrayIndex + 1, d_llong);
		}
		__syncthreads();
		arrayIndex += 1;
		if (arrayIndex + 1 < maxLimit) {
			if (d_llong[arrayIndex] > d_llong[arrayIndex + 1])
			{
				SWAP(t_llong, arrayIndex, arrayIndex + 1, d_llong);
			}
		}
		__syncthreads();
	}
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


///=============FROM cdpSimpleQuicksort example===============///
__device__ void selection_sort_int(int *data, int left, int right)
{
	for (int i = left; i <= right; ++i)
	{
		int min_val = data[i];
		int min_idx = i;

		// Find the smallest value in the range [left, right].
		for (int j = i + 1; j <= right; ++j)
		{
			int val_j = data[j];

			if (val_j < min_val)
			{
				min_idx = j;
				min_val = val_j;
			}
		}

		// Swap the values.
		if (i != min_idx)
		{
			data[min_idx] = data[i];
			data[i] = min_val;
		}
	}
}

__global__  void quicksort_int(int *data, int left, int right, int depth)
{
/*
	// If we're too deep or there are few elements left, we use an insertion sort...
	if (depth >= MAX_DEPTH || right - left <= INSERTION_SORT)
	{
		selection_sort_int(data, left, right);
		return;
	}

	int *lptr = data + left;
	int *rptr = data + right;
	int  pivot = data[(left + right) / 2];

	// Do the partitioning.
	while (lptr <= rptr)
	{
		// Find the next left- and right-hand values to swap
		int lval = *lptr;
		int rval = *rptr;

		// Move the left pointer as long as the pointed element is smaller than the pivot.
		while (lval < pivot)
		{
			lptr++;
			lval = *lptr;
		}

		// Move the right pointer as long as the pointed element is larger than the pivot.
		while (rval > pivot)
		{
			rptr--;
			rval = *rptr;
		}

		// If the swap points are valid, do the swap!
		if (lptr <= rptr)
		{
			*lptr++ = rval;
			*rptr-- = lval;
		}
	}

	// Now the recursive part
	int nright = rptr - data;
	int nleft = lptr - data;

	// Launch a new block to sort the left part.
	if (left < (rptr - data))
	{
		cudaStream_t s;
		cudaStreamCreateWithFlags(&s, cudaStreamNonBlocking);
		quicksort_int<<< 1, 1, 0, s >>>(data, left, nright, depth + 1);
		cudaStreamDestroy(s);
	}

	// Launch a new block to sort the right part.
	if ((lptr - data) < right)
	{
		cudaStream_t s1;
		cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
		quicksort_int<<< 1, 1, 0, s1 >>>(data, nleft, right, depth + 1);
		cudaStreamDestroy(s1);
	}
	*/
}

__global__ void quicksort_llong(long long * d_llong, size_t maxLimit)
{
	//Function body

}

__global__ void quicksort_string(std::string * d_string, size_t maxLimit)
{
	//Function body

}
