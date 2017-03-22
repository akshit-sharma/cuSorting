
#include "cuSource.h"
#include <cuda_runtime.h>

#include "GPU_Sorting_Functions.cuh"

void CuSource::sort() {
	switch (column_decide % 3)
	{
	case 0:
		break;
	case 1:
		// call sorting kernel with
		// d_paperIdWrapper
		switch (column_decide / 3)
		{
		case 2:
			odd_even_sort_scheme_paperid<<<NUM_BLOCK,WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
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

	//cudaMalloc((void **) d_schemeDataStructure, rows * sizeof(SchemeDataStructure));

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
		paperIdWrapper = (struct PaperIdWrapper_Scheme *) malloc(rows * sizeof(struct PaperIdWrapper_Scheme));
		for (size_t i = 0; i < rows; i++) {
			paperIdWrapper[i].paper_id = paper_id[i];
			paperIdWrapper[i].classPtr = &schemeDataStructure[i];
		}
		cudaMalloc((void **)d_paperIdWrapper, rows * sizeof(struct PaperIdWrapper_Scheme));
		cudaMemcpy(d_paperIdWrapper, paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper_Scheme),
			cudaMemcpyHostToDevice
		);
		free(paperIdWrapper);
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
	//cudaFree(d_schemeDataStructure);

	switch (column_decide % 3)
	{
	case 0:
		//	cudaFree(d_institution_name);
		//	delete[](h_institution_name);
		break;
	case 1:
		cudaFree(d_paperIdWrapper);
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
		cudaMemcpy(paperIdWrapper, d_paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper_Scheme),
			cudaMemcpyDeviceToHost
		);
		for (size_t i = 0; i < rows; i++) {
			schemeDataStructure[i] = *paperIdWrapper[i].classPtr;
		}
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

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_sm_gpu_");

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

	struct SchemeDSHolder schemeDSHolder;

	for (size_t i = 0; i < rows; i++)
	{

		schemeDataStructure[i].getValue(&schemeDSHolder);

		printf_stream(p_file, "%d,%s,%lld,%s,%s,%s,%d,%s,%d,%d,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s\n",
			schemeDSHolder.scheme_prog_code, schemeDSHolder.prog_name.c_str(), schemeDSHolder.scheme_id, schemeDSHolder.prog_sem_year.c_str(),
			schemeDSHolder.prepared_date.c_str(), schemeDSHolder.declared_date.c_str(), schemeDSHolder.institution_code, schemeDSHolder.institution_name.c_str(),
			schemeDSHolder.s_number, schemeDSHolder.paper_id, schemeDSHolder.paper_code.c_str(), schemeDSHolder.subject_name.c_str(), schemeDSHolder.credits,
			schemeDSHolder.type.c_str(), schemeDSHolder.exam.c_str(), schemeDSHolder.mode.c_str(), schemeDSHolder.kind.c_str(),
			schemeDSHolder.minor.c_str(), schemeDSHolder.major.c_str(), schemeDSHolder.max_marks.c_str(), schemeDSHolder.pass_marks.c_str())
			;

	}

	fclose(p_file);
}


