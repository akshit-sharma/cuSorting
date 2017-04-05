
#include "cuSource.h"
#include <cuda_runtime.h>
#include "Debugger.h"

#include "GPU_Sorting_Functions.cuh"

void CuSource::sort() {

	unsigned int num_blocks;

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
			//quicksort_scheme_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
			break;
		case 1:
			//shellsort_scheme_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
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
	}

}

void CuSource::MemAllo(const char* file_name)
{
	Source::MemAllo(file_name);

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
		break;
	case 2:
		// NOT READY
		//	cudaMalloc((void **)d_subject_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
		//	h_subject_name = new char[length_subject_name + 1];
		// TODO: cudaMemcpy
		break;
	}


}

void CuSource::preSorting()
{
	Source::preSorting();

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

}


void CuSource::MemFree()
{
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

	Source::MemFree();
}



void CuSource::postSorting()
{

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

}

void CuSource::write_file(const char * file_name, SchemeDataStructure * schemeDataStructure)
{
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
}


