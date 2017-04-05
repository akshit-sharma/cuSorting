
#include "cuBiggerSource.h"
#include <cuda_runtime.h>

#include "GPU_Sorting_Functions.cuh"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

void CuBiggerSource::sort() {

	unsigned int num_blocks;

	switch (column_decide % 3)
	{
	case 0:
		//call sorting kernel with
		//d_rollNumberWrapper
		switch ((column_decide - 1) / 3)
		{
		case 0:
			//quicksort_results_rollnumber<<<NUM_BLOCK, WID_BLOCK>>>(d_rollNumberWrapper);
			//cudaDeviceSynchronize();
			break;
		case 1:
			//shellsort_results_rollnumber<<<NUM_BLOCK, WID_BLOCK>>>(d_rollNumberWrapper);
			//cudaDeviceSynchronize();
			break;
		case 2:
			num_blocks = static_cast<int>(rows / WID_BLOCK) + 1;
			num_blocks = (num_blocks / 2) + 1;
			for (unsigned int i = 0; i < rows; i++) {
				odd_even_sort_llong<<<num_blocks, WID_BLOCK>>>(d_llong, rows);
				gpuErrchk(cudaPeekAtLastError());
				gpuErrchk(cudaDeviceSynchronize());
			}
			break;
		}
		break;
	case 1:
		//call sorting kernel with
		//d_paperIdWrapper
		switch ((column_decide-1) / 3)
		{
		case 0:
			//quicksort_results_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			//cudaDeviceSynchronize();
			break;
		case 1:
			//shellsort_results_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			//cudaDeviceSynchronize();
			break;
		case 2:
			num_blocks = static_cast<int>(rows / WID_BLOCK) + 1;
			num_blocks = (num_blocks / 2) + 1;
			for (unsigned int i = 0; i < rows; i++) {
				odd_even_sort_int<<<num_blocks, WID_BLOCK>>>(d_int, rows);
				gpuErrchk(cudaPeekAtLastError());
				gpuErrchk(cudaDeviceSynchronize());
			}
			break;
		default:
			break;
		}
		break;
	case 2:

		break;
	default:
		break;
	}
}


void CuBiggerSource::MemAllo(const char* file_name)
{
	BiggerSource::MemAllo(file_name);

	switch (column_decide % 3)
	{
	case 0:
		gpuErrchk(
			cudaMalloc((void **)&d_llong, rows * sizeof(long long))
		);
		break;
	case 1:
		gpuErrchk(
			cudaMalloc((void **)&d_int, rows * sizeof(int))
		);
		break;
	case 2:
		// NOT READY
		//	cudaMalloc((void **)name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_subject_name = new char[length_subject_name + 1];
		// TODO: cudaMemcpy
		break;
	}


}


void CuBiggerSource::preSorting()
{
	BiggerSource::preSorting();

	switch (column_decide % 3)
	{
	case 0:
		cudaMemcpy(d_llong, rollnumber,
			rows * sizeof(long long),
			cudaMemcpyHostToDevice
		);
		break;
	case 1:
		cudaMemcpy(d_int, paper_id,
			rows * sizeof(int),
			cudaMemcpyHostToDevice
		);
		break;
	case 2:
		// TODO: 
		break;
	}

}

void CuBiggerSource::MemFree() {

	switch (column_decide % 3)
	{
	case 0:
		cudaFree(d_llong);
		break;
	case 1:
		cudaFree(d_int);
		break;
	case 2:
		break;
	default:
		break;
	}

	BiggerSource::MemFree();

}


void CuBiggerSource::postSorting()
{
	switch (column_decide % 3)
	{
	case 0:
		cudaMemcpy(rollnumber, d_llong,
			rows * sizeof(long long),
			cudaMemcpyDeviceToHost
		);
		break;
	case 1:
		cudaMemcpy(paper_id, d_int,
			rows * sizeof(int),
			cudaMemcpyDeviceToHost
		);
		break;
	case 2:
		// TODO: 
		break;
	}

}

void CuBiggerSource::print_table(const char * file_name)
{
	FILE * p_file;
	std::string sorted_file_name(file_name);

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_big_gpu_");

	sorted_file_name += std::to_string(init_num);
	sorted_file_name += ".csv";

	fopen_stream(&p_file, sorted_file_name.c_str(), "w");

	for (size_t i = 0; i < rows; i++) {

		switch ((column_decide-1) % 3)
		{
		case 0:
			printf_stream(p_file, "%lld\n", rollnumber[i]);
			break;
		case 1:
			printf_stream(p_file, "%d\n", paper_id[i]);
			break;
		case 2:
			printf_stream(p_file, "%s\n", name[i].c_str());
			break;
		}

	}

	fclose(p_file);
}
