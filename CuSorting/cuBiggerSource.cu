
#include "cuBiggerSource.h"
#include <cuda_runtime.h>

#include "time.h"

#include "GPU_Sorting_Functions.cuh"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

double CuBiggerSource::sort() {

	cudaEvent_t start, stop;
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	int j, k;

	unsigned int num_blocks;
	unsigned int num_threads_per_block;
	size_t arr_size, num_arr;
	size_t left, right;
	float progress, last_prog;
	int h_ans;

	const int zero = 0;

	last_prog = 0.0f;

	switch (column_decide % 3)
	{
	case 0:
		//call sorting kernel with
		//d_rollNumberWrapper
		switch ((column_decide - 1) / 3)
		{
		case 0:
			left = 0;
			right = static_cast<size_t>(rows - 1);
			quicksort_llong<<< 1, 1 >>>(d_llong, left, right, 0);
			gpuErrchk(cudaPeekAtLastError());
			gpuErrchk(cudaDeviceSynchronize());
			break;
		case 1:
			num_blocks = max2Rows / THREADS + 1;
			for (k = 2; k <= max2Rows; k <<= 1) {
				for (j = k >> 1; j>0; j = j >> 1) {
					bitonic_sort_llong << <num_blocks, THREADS >> >(d_llong, j, k);
					gpuErrchk(cudaPeekAtLastError());
				}
			}
			break;
		case 2:
			num_blocks = static_cast<unsigned int>(rows / WID_BLOCK) + 1;
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
			gpuErrchk(cudaDeviceSetLimit(cudaLimitDevRuntimeSyncDepth, MAX_DEPTH));
			left = 0;
			right = static_cast<int>(rows - 1);
			quicksort_int<<< 1, 1>>>(d_int, left, right, 0);
			gpuErrchk(cudaPeekAtLastError());
			gpuErrchk(cudaDeviceSynchronize());
			break;
		case 1:
			num_blocks = max2Rows / THREADS + 1;
			for (k = 2; k <= max2Rows; k <<= 1) {
				for (j = k >> 1; j>0; j = j >> 1) {
					bitonic_sort_int << <num_blocks, THREADS >> >(d_int, j, k);
					gpuErrchk(cudaPeekAtLastError());
				}
			}
			break;
		case 2:
			num_blocks = static_cast<int>(rows / WID_BLOCK) + 1;
			num_blocks = (num_blocks / 2) + 1;
			for (unsigned int i = 0; i < rows; i++) {
				odd_even_sort_int<<<num_blocks, WID_BLOCK>>>(d_int, rows);
				gpuErrchk(cudaPeekAtLastError());
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

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return getTimeElapsed(start, stop);
	
}


double CuBiggerSource::MemAllo(const char* file_name)
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;
	c_start = startTimer();

	BiggerSource::MemAllo(file_name);

	c_end = endTimer();
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		gpuErrchk(
			cudaMalloc((void **)&d_llong, NUM_VALS * sizeof(long long))
		);
		break;
	case 1:
		gpuErrchk(
			cudaMalloc((void **)&d_int, NUM_VALS * sizeof(int))
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

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return  getTimeElapsed(c_start, c_end) + getTimeElapsed(start, stop);

}


double CuBiggerSource::preSorting()
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;
	c_start = startTimer();

	BiggerSource::preSorting();

	c_end = endTimer();
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		if (((column_decide - 1) / 3) == 1)
			bitonic_sort_llong_initMax <<<BLOCKS, THREADS >>>(d_llong, rows);
		gpuErrchk(
			cudaMemcpy(d_llong, rollnumber,
				rows * sizeof(long long),
				cudaMemcpyHostToDevice
			)
		);
		break;
	case 1:
		if (((column_decide - 1) / 3) == 1)
			bitonic_sort_int_initMax << <BLOCKS, THREADS >> >(d_int, rows);
		gpuErrchk(
			cudaMemcpy(d_int, paper_id,
				rows * sizeof(int),
				cudaMemcpyHostToDevice
			)
		);
		break;
	case 2:
		// TODO: 
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return  getTimeElapsed(c_start, c_end) + getTimeElapsed(start, stop);

}

double CuBiggerSource::MemFree() {

	clock_t c_start, c_end;
	cudaEvent_t start, stop;

	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		gpuErrchk(
			cudaFree(d_llong)
		);
		break;
	case 1:
		gpuErrchk(
			cudaFree(d_int)
		);
		break;
	case 2:
		break;
	default:
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	c_start = startTimer();

	BiggerSource::MemFree();

	c_end = endTimer();

	return  getTimeElapsed(c_start, c_end) + getTimeElapsed(start, stop);

}


double CuBiggerSource::postSorting()
{
	cudaEvent_t start, stop;

	initializeTimer(&start, &stop);
	timerEventRecord(&start);

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

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return getTimeElapsed(start, stop);

}

double CuBiggerSource::print_table(const char * file_name)
{
	clock_t c_start, c_end;

	c_start = startTimer();

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

	c_end = endTimer();

	return  getTimeElapsed(c_start, c_end);
}

void CuBiggerSource::initializeTimer(cudaEvent_t * start, cudaEvent_t * end)
{
	cudaEventCreate(start);
	cudaEventCreate(end);
}

void CuBiggerSource::timerEventRecord(cudaEvent_t * timer)
{
	cudaEventRecord(*timer);
}

void CuBiggerSource::timerEventSync(cudaEvent_t * timer)
{
	cudaEventSynchronize(*timer);
}

double CuBiggerSource::getTimeElapsed(cudaEvent_t start, cudaEvent_t end)
{
	float milliseconds = 0;

	cudaEventElapsedTime(&milliseconds, start, end);

	return milliseconds / 1000;
}

clock_t CuBiggerSource::startTimer()
{
	return clock();
}

clock_t CuBiggerSource::endTimer()
{
	return clock();
}

double CuBiggerSource::getTimeElapsed(clock_t start, clock_t end)
{
	return (end - start) / static_cast<double>(CLOCKS_PER_SEC);
}

