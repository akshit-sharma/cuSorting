#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

__global__ void odd_even_sort_int_xtra(int * d_int, size_t maxLimit, size_t num_arr, size_t arr_size)
{
	size_t arrayIndex;
	size_t arr_end;
	int t_int;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;

	arrayIndex = arrayIndex * 2;

		if (((arrayIndex + 1) < maxLimit) && ((arrayIndex + 1) % arr_size != 0)) {
			if (d_int[arrayIndex] == 0) {
				printf("0 at %llu\n", arrayIndex);
			}
			if (d_int[arrayIndex + 1] == 0) {
				printf("0 at %llu\n", arrayIndex + 1);
			}
			if (d_int[arrayIndex] > d_int[arrayIndex + 1])
			{
				SWAP(t_int, arrayIndex, arrayIndex + 1, d_int);
			}
			__syncthreads();
			arrayIndex += 1;
			if (((arrayIndex + 1) < maxLimit) && ((arrayIndex + 1) % arr_size != 0)) {
				if (d_int[arrayIndex] == 0) {
					printf("0 at %llu\n", arrayIndex);
				}
				if (d_int[arrayIndex + 1] == 0) {
					printf("0 at %llu\n", arrayIndex + 1);
				}
				if (d_int[arrayIndex] > d_int[arrayIndex + 1])
				{
					SWAP(t_int, arrayIndex, arrayIndex + 1, d_int);
				}
			}
			__syncthreads();
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

__global__ void shellsort_int(int * d_int, size_t maxLimit, size_t num_arr, size_t arr_size, int * d_xtra_int)
{
	size_t arrayIndex;
	int t_int;
	size_t calcIndex;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;

	calcIndex = ((arrayIndex % num_arr) * arr_size) + (arrayIndex / num_arr);

	if (arrayIndex >= maxLimit)
		return;

	d_xtra_int[calcIndex] = d_int[arrayIndex];

	
	if (d_xtra_int[calcIndex] == 0) {
		printf("Value of %llu is %d is stored as %d at %llu\n", arrayIndex, d_int[arrayIndex], d_xtra_int[calcIndex], calcIndex);
	}
	
	if (d_int[arrayIndex] == 0) {
		printf("Value of %llu is %d is stored as %d at %llu\n", arrayIndex, d_int[arrayIndex], d_xtra_int[calcIndex], calcIndex);
	}

	if (arrayIndex / 2 == 131010) {
		printf("Value of %llu is %d is stored as %d at %llu\n", arrayIndex, d_int[arrayIndex], d_xtra_int[calcIndex], calcIndex);
	}
	if ((calcIndex == 262020) || (calcIndex == 262021)) {
		printf("Value of %llu is %d is stored as %d at %llu\n", arrayIndex, d_int[arrayIndex], d_xtra_int[calcIndex], calcIndex);
	}
	
}

__global__ void shellsort_int_back(int * d_int, size_t maxLimit, size_t num_arr, size_t arr_size, int * d_xtra_int)
{
	size_t arrayIndex;
	int t_int;
	size_t calcIndex;

	arrayIndex = threadIdx.x + blockIdx.x*blockDim.x;

	calcIndex = ((arrayIndex % num_arr) * arr_size) + (arrayIndex / num_arr);

	if (arrayIndex >= maxLimit)
		return;

	d_int[arrayIndex] = d_xtra_int[calcIndex];

//	if (arrayIndex / 2 == 1) {
//		printf("Value of %llu is %d is stored as %d at %llu\n", arrayIndex, d_int[arrayIndex], d_xtra_int[calcIndex], calcIndex);
//	}

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
__device__ void selection_sort_int(int *data, size_t left, size_t right)
{
	for (int i = left; i <= right; ++i)
	{
		int min_val = data[i];
		size_t min_idx = i;

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

__global__  void quicksort_int(int *data, size_t left, size_t right, size_t depth)
{

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
	size_t nright = rptr - data;
	size_t nleft = lptr - data;

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
	
}


///=============modified cdpSimpleQuicksort example===============///
__device__ void selection_sort_llong(long long * data, size_t left, size_t right)
{
	for (size_t i = left; i <= right; ++i)
	{
		long long min_val = data[i];
		size_t min_idx = i;

		// Find the smallest value in the range [left, right].
		for (size_t j = i + 1; j <= right; ++j)
		{
			long long val_j = data[j];

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

__global__ void quicksort_llong(long long * data, size_t left, size_t right, size_t depth)
{

	// If we're too deep or there are few elements left, we use an insertion sort...
	if (depth >= MAX_DEPTH || right - left <= INSERTION_SORT)
	{
		selection_sort_llong(data, left, right);
		return;
	}

	long long *lptr = data + left;
	long long *rptr = data + right;
	long long  pivot = data[(left + right) / 2];

	// Do the partitioning.
	while (lptr <= rptr)
	{
		// Find the next left- and right-hand values to swap
		long long lval = *lptr;
		long long rval = *rptr;

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
	size_t nright = rptr - data;
	size_t nleft = lptr - data;

	// Launch a new block to sort the left part.
	if (left < (rptr - data))
	{
		cudaStream_t s;
		cudaStreamCreateWithFlags(&s, cudaStreamNonBlocking);
		quicksort_llong<<< 1, 1, 0, s >>>(data, left, nright, depth + 1);
		cudaStreamDestroy(s);
	}

	// Launch a new block to sort the right part.
	if ((lptr - data) < right)
	{
		cudaStream_t s1;
		cudaStreamCreateWithFlags(&s1, cudaStreamNonBlocking);
		quicksort_llong<<< 1, 1, 0, s1 >>>(data, nleft, right, depth + 1);
		cudaStreamDestroy(s1);
	}

}


__global__ void quicksort_string(std::string * d_string, size_t maxLimit)
{
	//Function body

}
