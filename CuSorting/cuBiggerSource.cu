
#include "cuBiggerSource.h"
#include <cuda_runtime.h>

#include "GPU_Sorting_Functions.cuh"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

void CuBiggerSource::sort() {
	switch (column_decide % 3)
	{
	case 0:
		//call sorting kernel with
		//d_paperIdWrapper
		switch (column_decide / 3)
		{
		case 2:
			odd_even_sort_results_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
		default:
			break;
		}
		break;
	case 1:

		break;
	case 2:
		//call sorting kernel with
		//d_rollNumberWrapper
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
		paperIdWrapper = (struct PaperIdWrapper_Results *) malloc(rows * sizeof(struct PaperIdWrapper_Results));
		for (size_t i = 0; i < rows; i++) {
			paperIdWrapper[i].paper_id = paper_id[i];
			paperIdWrapper[i].classPtr = &resultsDataStructure[i];
		}
		cudaMalloc((void **)d_paperIdWrapper, rows * sizeof(struct PaperIdWrapper_Results));
		cudaMemcpy(d_paperIdWrapper, paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper_Results),
			cudaMemcpyHostToDevice
		);
		break;
	case 1:
		// TODO: 
		break;
	case 2:
		rollNumberWrapper = (struct RollNumberWrapper_Results *) malloc(rows * sizeof(struct RollNumberWrapper_Results));
		for (size_t i = 0; i < rows; i++) {
			rollNumberWrapper[i].rollnumber = rollnumber[i];
			rollNumberWrapper[i].classPtr = &resultsDataStructure[i];
		}
		cudaMalloc((void **)d_rollNumberWrapper, rows * sizeof(struct PaperIdWrapper_Results));
		cudaMemcpy(d_rollNumberWrapper, rollNumberWrapper,
			rows * sizeof(struct PaperIdWrapper_Results),
			cudaMemcpyHostToDevice
		);
		break;

	}

}

void CuBiggerSource::MemFree() {

	switch (column_decide % 3)
	{
	case 0:
		cudaFree(d_paperIdWrapper);
		free(paperIdWrapper);
		break;
	case 1:
		break;
	case 2:
		cudaFree(d_rollNumberWrapper);
		free(rollNumberWrapper);
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
		cudaMemcpy(paperIdWrapper, d_paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper_Results),
			cudaMemcpyDeviceToHost
		);
		for (size_t i = 0; i < rows; i++) {
			resultsDataStructure[i] = *paperIdWrapper[i].classPtr;
		}
		break;
	case 1:
		// TODO: 
		break;
	case 2:
		cudaMemcpy(rollNumberWrapper, d_rollNumberWrapper,
			rows * sizeof(struct PaperIdWrapper_Results),
			cudaMemcpyDeviceToHost
		);
		for (size_t i = 0; i < rows; i++) {
			resultsDataStructure[i] = *rollNumberWrapper[i].classPtr;
		}
		break;
	}

}

void CuBiggerSource::write_file(const char * file_name, ResultsDataStructure * resultsDataStructure)
{
	FILE * p_file;
	std::string sorted_file_name(file_name);

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_big_gpu_");

	sorted_file_name += std::to_string(init_num);
	sorted_file_name += ".csv";

	fopen_stream(&p_file, sorted_file_name.c_str(), "w");

	std::vector<std::string>::iterator iter;
	for (iter = headers.begin();
		iter != headers.end(); ++iter) {
		if (iter != headers.begin())
			printf_stream(p_file, ",");
		printf_stream(p_file, "%s", (*iter).c_str());
	}

	printf_stream(p_file, "\n");

	struct ResultsDSHolder resultsDSHolder;

	for (size_t i = 0; i < rows; i++) {

		resultsDataStructure[i].getValue(&resultsDSHolder);

		printf_stream(p_file, "%d,%s,%s,%s,%s,%d,%s,%d,%s,%lld,%s,%lld,%lld,%d,%s,%s,%s,%s\n",
			resultsDSHolder.scheme_prog_code, resultsDSHolder.prepared_date.c_str(),
			resultsDSHolder.declared_date.c_str(), resultsDSHolder.prog_name.c_str(),
			resultsDSHolder.prog_sem_year.c_str(), resultsDSHolder.batch,
			resultsDSHolder.examination.c_str(), resultsDSHolder.institution_code,
			resultsDSHolder.institution_name.c_str(), resultsDSHolder.rollnumber,
			resultsDSHolder.name.c_str(), resultsDSHolder.sid, resultsDSHolder.result_scheme_id,
			resultsDSHolder.paper_id, resultsDSHolder.credits.c_str(), resultsDSHolder.minor.c_str(),
			resultsDSHolder.major.c_str(), resultsDSHolder.total.c_str());

	}

	fclose(p_file);
}
