#pragma once
#include "BiggerSource.h"
#include "cuRDStruct.h"

class CuBiggerSource : public BiggerSource
{

	int * d_int;
	long long * d_llong;

	void write_file(const char * file_name, 
		ResultsDataStructure * resultsDataStructure);

public:
	virtual void MemAllo(const char* file_name);
	virtual void preSorting();
	virtual void sort();
	virtual void postSorting();
	virtual void print_table(const char * file_name);
	virtual void MemFree();

};

