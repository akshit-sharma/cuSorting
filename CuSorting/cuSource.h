#pragma once
#include "Source.h"
#include "cuSDStruct.h"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

class CuSource : public Source
{
	
	struct PaperIdWrapper_Scheme * d_paperIdWrapper;
	struct PaperIdWrapper_Scheme * paperIdWrapper;


	void write_file(const char * file_name,
		SchemeDataStructure * schemeDataStructure);

public:
	virtual void MemAllo(const char* file_name);
	virtual void sort();
	virtual void postSorting();
	virtual void MemFree();

};

