
#include "cuBiggerSource.h"
#include <cuda_runtime.h>

void CuBiggerSource::sort(int column) {
	switch (column %3)
	{
	case 0:
		//call sorting kernel with
		//d_paperIdWrapper
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
	CuBiggerSource::MemAllo(file_name);

	switch (column % 3)
	{
	case 0:
		paperIdWrapper = (struct PaperIdWrapper *) malloc(rows * sizeof(struct PaperIdWrapper));
		for (size_t i = 0; i < rows; i++) {
			paperIdWrapper[i].paper_id = paper_id[i];
			paperIdWrapper[i].classPtr = &resultsDataStructure[i];
		}
		cudaMalloc((void **)d_paperIdWrapper, rows * sizeof(struct PaperIdWrapper));
		cudaMemcpy(d_paperIdWrapper, paperIdWrapper,
			rows * sizeof(struct PaperIdWrapper),
			cudaMemcpyHostToDevice
		);
		break;
	case 1:
		// TODO: 
		break;
	case 2:
		rollNumberWrapper = (struct RollNumberWrapper *) malloc(rows * sizeof(struct RollNumberWrapper));
		for (size_t i = 0; i < rows; i++) {
			rollNumberWrapper[i].rollnumber = rollnumber[i];
			rollNumberWrapper[i].classPtr = &resultsDataStructure[i];
		}
		cudaMalloc((void **)d_rollNumberWrapper, rows * sizeof(struct PaperIdWrapper));
		cudaMemcpy(d_rollNumberWrapper, rollNumberWrapper,
			rows * sizeof(struct PaperIdWrapper),
			cudaMemcpyHostToDevice
		);
		break;

	}

}

void CuBiggerSource::MemFree() {

	switch (column % 3)
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


