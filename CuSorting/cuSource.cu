
#include "cuSource.h"
#include <cuda_runtime.h>

#include "time.h"

#include "GPU_Sorting_Functions.cuh"

double CuSource::sort() {
	
	clock_t c_start, c_end;
	c_start = startTimer();

	int j, k;

	unsigned int num_blocks;
	unsigned int num_threads_per_block;
	bool sorted;
	int pre_val;
	size_t arr_size, num_arr;
	size_t left, right;
	size_t gpu_loop;

	switch (column_decide % 3)
	{
	case 0:
		break;
	case 1:
		// call sorting kernel with
		// d_paperIdWrapper
		switch ((column_decide - 1) / 3)
		{
		case 0:
			gpuErrchk(cudaDeviceSetLimit(cudaLimitDevRuntimeSyncDepth, MAX_DEPTH));
			left = 0;
			right = static_cast<size_t>(rows - 1);
			quicksort_int<<< 1, 1>>>(d_int, left, right, 0);
			gpuErrchk(cudaPeekAtLastError());
			gpuErrchk(cudaDeviceSynchronize());
			break;
		case 1:
			for (k = 2; k <= NUM_VALS; k <<= 1) {
				for (j = k >> 1; j>0; j = j >> 1) {
					bitonic_sort_int <<<BLOCKS, THREADS >>>(d_int, j, k);
					gpuErrchk(cudaPeekAtLastError());
				}
			}
			break;
		case 2:
			gpu_loop = 1024;
			num_blocks = static_cast<unsigned int>(rows / WID_BLOCK) + 1;
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
	}

	c_end = endTimer();
	return getTimeElapsed(c_start, c_end);

}

double CuSource::MemAllo(const char* file_name)
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;
	c_start = startTimer();

	Source::MemAllo(file_name);

	c_end = endTimer();
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		// NOT READY
		//	cudaMalloc((void **)d_institution_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_institution_name = new char[length_institution_name + 1];
		// TODO: cudaMemcpy
		break;
	case 1:
		if (((column_decide - 1) / 3) == 1)
		{
			gpuErrchk(
				cudaMalloc((void **)&d_int, NUM_VALS * sizeof(TYPE_PAPER_ID))
			);
		}
		else {
			gpuErrchk(
				cudaMalloc((void **)&d_int, rows * sizeof(TYPE_PAPER_ID))
			);
		}
		break;
	case 2:
		// NOT READY
		//	cudaMalloc((void **)d_subject_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_subject_name = new char[length_subject_name + 1];
		// TODO: cudaMemcpy
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return  getTimeElapsed(c_start, c_end)+getTimeElapsed(start, stop);
}

double CuSource::preSorting()
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;
	size_t i;

	c_start = startTimer();

	Source::preSorting();

	c_end = endTimer();
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		// NOT READY
		//	cudaMalloc((void **)d_institution_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_institution_name = new char[length_institution_name + 1];
		// TODO: cudaMemcpy
		break;
	case 1:
		if (((column_decide - 1) / 3) == 1)
			bitonic_sort_int_initMax<<<BLOCKS, THREADS>>>(d_int);
		gpuErrchk(
			cudaMemcpy(d_int, paper_id,
				rows * sizeof(int),
				cudaMemcpyHostToDevice
			)
		);
		break;
	case 2:
		// NOT READY
		//	cudaMalloc((void **)d_subject_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_subject_name = new char[length_subject_name + 1];
		// TODO: cudaMemcpy
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return  getTimeElapsed(c_start, c_end) + getTimeElapsed(start, stop);

}


double CuSource::MemFree()
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;

	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	switch (column_decide % 3)
	{
	case 0:
		//	cudaFree(d_institution_name);
		//	delete[](h_institution_name);
		break;
	case 1:
		gpuErrchk(
			cudaFree(d_int)
		);
		break;
	case 2:
		//	cudaFree(d_subject_name);
		//	delete[](h_subject_name);
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	c_start = startTimer();

	Source::MemFree();

	c_end = endTimer();

	return  getTimeElapsed(c_start, c_end) + getTimeElapsed(start, stop);

}



double CuSource::postSorting()
{
	clock_t c_start, c_end;
	cudaEvent_t start, stop;

	initializeTimer(&start, &stop);
	timerEventRecord(&start);

	int t_int;
	size_t i;

	switch (column_decide % 3)
	{
	case 0:
		//	cudaFree(d_institution_name);
		//	delete[](h_institution_name);
		break;
	case 1:
		gpuErrchk(
			cudaMemcpy(paper_id, d_int,
				rows * sizeof(int),
				cudaMemcpyDeviceToHost
			)
		);
		break;
	case 2:
		//	cudaFree(d_subject_name);
		//	delete[](h_subject_name);
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return getTimeElapsed(start, stop);

}

double CuSource::print_table(const char * file_name)
{
	clock_t c_start, c_end;

	c_start = startTimer();

	FILE * p_file;
	std::string sorted_file_name(file_name);
	int i_value;
	std::string s_value;

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_sm_gpu_");

	sorted_file_name += std::to_string(init_num);
	sorted_file_name += ".csv";

	fopen_stream(&p_file, sorted_file_name.c_str(), "w");
	
	for (size_t i = 0; i < rows; i++)
	{

		switch (column_decide % 3)
		{
		case 0:
			s_value = sorted_col_string[i];
			printf_stream(p_file, "%s\n", s_value.c_str());
			break;
		case 1:
			printf_stream(p_file, "%d\n", paper_id[i]);
			break;
		case 2:
			s_value = sorted_col_string[i];
			printf_stream(p_file, "%s\n", s_value.c_str());
			break;
		}

	}

	fclose(p_file);

	c_end = endTimer();

	return  getTimeElapsed(c_start, c_end);

}

void CuSource::initializeTimer(cudaEvent_t * start, cudaEvent_t * end) 
{
	cudaEventCreate(start);
	cudaEventCreate(end);
}

void CuSource::timerEventRecord(cudaEvent_t * timer)
{
	cudaEventRecord(*timer);
}

void CuSource::timerEventSync(cudaEvent_t * timer)
{
	cudaEventSynchronize(*timer);
}

double CuSource::getTimeElapsed(cudaEvent_t start, cudaEvent_t end)
{
	float milliseconds = 0;

	cudaEventElapsedTime(&milliseconds, start, end);

	return milliseconds/1000;
}

clock_t CuSource::startTimer()
{
	return clock();
}

clock_t CuSource::endTimer()
{
	return clock();
}

double CuSource::getTimeElapsed(clock_t start, clock_t end)
{
	return (end - start) / static_cast<double>(CLOCKS_PER_SEC);
}

