#pragma once
#include "Source.h"
#include "cuSDStruct.h"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

#define TYPE_PAPER_ID decltype(paper_id)

class CuSource : public Source
{
	
	int * d_int;

	void write_file(const char * file_name,
		SchemeDataStructure * schemeDataStructure);

public:
	virtual void MemAllo(const char* file_name);
	virtual void preSorting();
	virtual void sort();
	virtual void postSorting();
	virtual void MemFree();

};

