
#include "cuSource.h"
#include <cuda_runtime.h>

#include "time.h"

#include "GPU_Sorting_Functions.cuh"

double CuSource::sort() {

	cudaEvent_t start, stop;
	initializeTimer(&start, &stop);
	timerEventRecord(&start);

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
			for (unsigned int i = rows/2; i > 0; i /= 2) {
				num_threads_per_block = rows;
				num_arr = i + 1;
				if ((num_threads_per_block - 1) / WID_BLOCK > 0) {
					num_blocks = (num_threads_per_block / WID_BLOCK) + 1;
					num_threads_per_block = WID_BLOCK;
				}
				arr_size = rows / i;
				
				//transfer data from d_int to d_xtra_int
				shellsort_int << <num_blocks, num_threads_per_block >> >(d_int, rows, num_arr-1, arr_size, d_xtra_int);
				gpuErrchk(cudaPeekAtLastError());
				gpuErrchk(cudaDeviceSynchronize());
				/*
				gpuErrchk(
					cudaMemcpy(paper_id, d_xtra_int,
						rows * sizeof(int),
						cudaMemcpyDeviceToHost
					)
				);
				printf_stream(stdout, "Xtra_Arr (Source.cu) Array size %d \n %5d", i, 0);
				for (unsigned int i = 0; i < rows; i++) {
					if(paper_id[i] == 0)
					printf_stream(stdout, " \n %5d %7d", i, paper_id[i]);

//					if ((i + 1) % arr_size == 0)
//						printf_stream(stdout, " \n %5d",(i+1)/arr_size);
				}
				printf_stream(stdout, " \n");
				*/

				//odd_even_sort_int_xtra(int * d_int, size_t maxLimit, size_t offset)
				gpu_loop = 1024;
				num_blocks = static_cast<unsigned int>(rows / WID_BLOCK) + 1;
				num_blocks = (num_blocks / 2) + 1;
				for (unsigned int i = 0; i < (arr_size/2)+1; i++) {
					odd_even_sort_int_xtra <<<num_blocks, WID_BLOCK >> >(d_xtra_int, rows, num_arr, arr_size);
					gpuErrchk(cudaPeekAtLastError());
					gpuErrchk(cudaDeviceSynchronize());
				}
				
				sorted = true;
				gpuErrchk(
					cudaMemcpy(paper_id, d_xtra_int,
						rows * sizeof(int),
						cudaMemcpyDeviceToHost
					)
				);
				pre_val = INT_MIN;
				for (unsigned int i = 0; i < rows; i++) {
					if (pre_val > paper_id[i]) {
						sorted = false;
						printf_stream(stdout, "Elements %7d(%7d) and %7d(%7d) not sorted",paper_id[i-1],i-1,paper_id[i],i);
						break;
					}
					pre_val = paper_id[i];

					if ((i + 1) % arr_size == 0)
						pre_val = INT_MIN;
				}
				if (!sorted) {
					printf_stream(stdout, "Xtra_Arr (Source.cu) Array size %d \n %5d", i, 0);
					for (unsigned int i = 0; i < rows; i++) {
						printf_stream(stdout, " %7d", paper_id[i]);

						if ((i + 1) % arr_size == 0)
							printf_stream(stdout, " \n %5d", (i + 1) / arr_size);
					}
					printf_stream(stdout, " \n");
				}
				
				num_threads_per_block = rows;
				if ((num_threads_per_block - 1) / WID_BLOCK > 0) {
					num_blocks = (num_threads_per_block / WID_BLOCK) + 1;
					num_threads_per_block = WID_BLOCK;
				}
				arr_size = rows / i;

				//transfer data from d_int to d_xtra_int
				if (i == 1) {
					gpuErrchk(
						cudaMemcpy(d_int, d_xtra_int,
							rows * sizeof(int),
							cudaMemcpyDeviceToDevice
						)
					);
				}
				else {
					shellsort_int_back << <num_blocks, num_threads_per_block >> > (d_int, rows, num_arr-1, arr_size, d_xtra_int);
					gpuErrchk(cudaPeekAtLastError());
					gpuErrchk(cudaDeviceSynchronize());
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
				gpuErrchk(cudaDeviceSynchronize());
			}
			break;
		default:
			break;
		}
		break;
	case 2:
		break;
	}

	timerEventRecord(&stop);
	timerEventSync(&stop);

	return getTimeElapsed(start, stop);

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
		gpuErrchk(
			cudaMalloc((void **)&d_int, rows * sizeof(TYPE_PAPER_ID))
		);
		gpuErrchk(
			cudaMalloc((void **)&d_xtra_int, rows * sizeof(TYPE_PAPER_ID))
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
			cudaFree(d_xtra_int)
		);
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
		/*
		t_int = paper_id[0];
		for (i = 0; i < rows; i++) {
			if (paper_id[i + 1] == t_int) {
				paper_id[i] = t_int;
				break;
			}
			if (paper_id[i+1] < t_int)
			{
				paper_id[i] = paper_id[i + 1];
			}
		}
		*/
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

