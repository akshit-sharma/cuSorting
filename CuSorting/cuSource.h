#pragma once
#include "Source.h"
#include "cuSDStruct.h"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

#define TYPE_PAPER_ID decltype(TYPE_PaperIdWrapper_Scheme.paper_id)
#define TYPE_CLASSPTR decltype(TYPE_PaperIdWrapper_Scheme.classPtr)

class CuSource : public Source
{
	
	const struct PaperIdWrapper_Scheme TYPE_PaperIdWrapper_Scheme = { 0 };

	struct PaperIdWrapper_Scheme * d_paperIdWrapper;
	struct PaperIdWrapper_Scheme * paperIdWrapper;

	TYPE_PAPER_ID * d_paper_id;
	TYPE_PAPER_ID * h_paper_id;
	TYPE_CLASSPTR * d_classPtr;
	TYPE_CLASSPTR * h_classPtr;

	void write_file(const char * file_name,
		SchemeDataStructure * schemeDataStructure);

public:
	virtual void MemAllo(const char* file_name);
	virtual void preSorting();
	virtual void sort();
	virtual void postSorting();
	virtual void MemFree();

};

