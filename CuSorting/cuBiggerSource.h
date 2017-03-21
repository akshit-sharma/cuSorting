#pragma once
#include "BiggerSource.h"
#include "cuRDStruct.h"

class CuBiggerSource : public BiggerSource
{
	struct PaperIdWrapper_Results * paperIdWrapper;
	struct RollNumberWrapper_Results * rollNumberWrapper;

	struct PaperIdWrapper_Results * d_paperIdWrapper;
	struct RollNumberWrapper_Results * d_rollNumberWrapper;

	void write_file(const char * file_name, 
		ResultsDataStructure * resultsDataStructure);

public:
	virtual void MemAllo(const char* file_name);
	virtual void sort(int column);
	virtual void postSorting();
	virtual void print_table(const char * file_name);
	virtual void MemFree();

};

