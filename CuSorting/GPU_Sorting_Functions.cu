#include "GlobalHeader.h"
#include "device_launch_parameters.h"
#include "GPU_Sorting_Functions.cuh"
#include "cuRDStruct.h"
#include "cuSDStruct.h"
#include "SchemeDataStructure.h"
#include "cuSource.h"

__global__ void bitonic_sort_int_initMax(int *dev_values)
{
	size_t i;

	i = threadIdx.x + blockDim.x * blockIdx.x;

	dev_values[i] = INT_MAX;
}

__global__ void bitonic_sort_llong_initMax(long long *dev_values)
{
	size_t i;

	i = threadIdx.x + blockDim.x * blockIdx.x;

	dev_values[i] = LONG_MAX;
}

__global__ void bitonic_sort_int(int *dev_values, int j, int k)
{
	unsigned int i, ixj;
	i = threadIdx.x + blockDim.x * blockIdx.x;
	ixj = i^j;

	if ((ixj) > i) {
		if ((i&k) == 0) {
			if (dev_values[i] > dev_values[ixj]) {
				int temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
		if ((i&k) != 0) {
			if (dev_values[i] < dev_values[ixj]) {
				int temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
	}
}

__global__ void bitonic_sort_llong(long long *dev_values, int j, int k)
{
	unsigned int i, ixj; 
	i = threadIdx.x + blockDim.x * blockIdx.x;
	ixj = i^j;

	if ((ixj) > i) {
		if ((i&k) == 0) {
			if (dev_values[i] > dev_values[ixj]) {
				long long temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
		}
		if ((i&k) != 0) {
			if (dev_values[i] < dev_values[ixj]) {
				long long temp = dev_values[i];
				dev_values[i] = dev_values[ixj];
				dev_values[ixj] = temp;
			}
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
