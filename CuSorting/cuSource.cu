
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
			quicksort_scheme_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
			break;
		case 1:
			shellsort_scheme_paperid<<<NUM_BLOCK, WID_BLOCK>>>(d_paperIdWrapper);
			cudaDeviceSynchronize();
			break;
		case 2:
			num_blocks = static_cast<int>(rows / WID_BLOCK) + 1;
			num_blocks = (num_blocks / 2) + 1;
			//print_debug_specific
			for (unsigned int i = 0; i < rows; i++) {
				odd_even_sort_scheme_paperid<<<num_blocks, WID_BLOCK>>>(d_paperIdWrapper, rows);
				gpuErrchk(cudaPeekAtLastError());
				gpuErrchk(cudaDeviceSynchronize());
			}
			//checkArray<<<static_cast<int>(rows / WID_BLOCK) + 1, WID_BLOCK>>>(d_paperIdWrapper, rows);
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
		paperIdWrapper = (struct PaperIdWrapper_Scheme *) malloc(rows * sizeof(struct PaperIdWrapper_Scheme));
		gpuErrchk(
			cudaMalloc((void **)&d_paperIdWrapper, rows * sizeof(struct PaperIdWrapper_Scheme))
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
		for (size_t i = 0; i < rows; i++) {
			paperIdWrapper[i].paper_id = paper_id[i];
			paperIdWrapper[i].classPtr = &schemeDataStructure[i];

			//	printf_stream(stderr, "class add not same \n %p is before %p \n\n",
			//		&schemeDataStructure[i], paperIdWrapper[i].classPtr);
		}
		//copy_data(paperIdWrapper, rows);
		gpuErrchk(
			cudaMemcpy(d_paperIdWrapper, paperIdWrapper,
				rows * sizeof(struct PaperIdWrapper_Scheme),
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
	//cudaFree(d_schemeDataStructure);

	switch (column_decide % 3)
	{
	case 0:
		//	cudaFree(d_institution_name);
		//	delete[](h_institution_name);
		break;
	case 1:
		gpuErrchk(
			cudaFree(d_paperIdWrapper)
		);
		free(paperIdWrapper);
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
			cudaMemcpy(paperIdWrapper, d_paperIdWrapper,
				rows * sizeof(struct PaperIdWrapper_Scheme),
				cudaMemcpyDeviceToHost
			));
		//print_debug_specific
		//check_data(paperIdWrapper);
		//remove_data();
		int paper_id_old;
		int paper_id_new;
		int wrongCount;
		int wrongCombination;
		SchemeDataStructure * tempSchemeDataStructure;
		paper_id_old = INT_MIN;
		wrongCount = 0;
		wrongCombination = 0;
		for (size_t i = 0; i < rows; i++) {
			paper_id_new = paperIdWrapper[i].paper_id;
			if (paper_id_new < paper_id_old) {
				wrongCount++;
			}
			tempSchemeDataStructure = paperIdWrapper[i].classPtr;
			if (paper_id_new != tempSchemeDataStructure->getPaperId()) {
//				printf("%d %d not same", paper_id_new, tempSchemeDataStructure->getPaperId());
			}
			auto originalValue = tempSchemeDataStructure->getOriginalValue();
			schemeDataStructure[i].setValue(&originalValue);
			if (paper_id_new != schemeDataStructure[i].getPaperId()) {
				wrongCombination++;
			}
			paper_id_old = paper_id_new;
		}
		printf_stream(stdout, "Wrongly sorted elements %d and combination %d \n", wrongCount, wrongCombination);
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


