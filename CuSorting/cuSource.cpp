
#include "cuSource.h"
#include <cuda_runtime.h>

void CuSource::sort(int column) {
	switch (column % 3)
	{
	case 0:
		break;
	case 1:
		// call sorting kernel with
		// d_paperIdWrapper
		break;
	case 2:
		break;
	}

}

void CuSource::MemAllo(const char* file_name)
{
	Source::MemAllo(file_name);

	//cudaMalloc((void **) d_schemeDataStructure, rows * sizeof(SchemeDataStructure));

	switch (column % 3)
	{
	case 0:
		// NOT READY
	//	cudaMalloc((void **)d_institution_name, rows * sizeof(char));
		// TODO: fig. out a way for string to gpu
	//	h_institution_name = new char[length_institution_name + 1];
		// TODO: cudaMemcpy
		break;
	case 1:
		paperIdWrapper = (struct PaperIdWrapper *) malloc(rows*sizeof(struct PaperIdWrapper));
		for (size_t i = 0; i < rows; i++) {
			paperIdWrapper[i].paper_id = paper_id[i];
			paperIdWrapper[i].classPtr = &schemeDataStructure[i];
		}
		cudaMalloc((void **)d_paperIdWrapper, rows * sizeof(struct PaperIdWrapper));
		cudaMemcpy(d_paperIdWrapper, paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper),
			cudaMemcpyHostToDevice
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

	switch (column % 3)
	{
	case 0:
	//	cudaFree(d_institution_name);
	//	delete[](h_institution_name);
		break;
	case 1:
		cudaFree(d_paperIdWrapper);
		free(paperIdWrapper);
		break;
	case 2:
	//	cudaFree(d_subject_name);
	//	delete[](h_subject_name);
		break;
	}

	Source::MemFree();
}

