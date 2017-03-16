#pragma once
#include "Source.h"
#include "cuSDStruct.h"

class CuSource : protected Source
{
	
	struct PaperIdWrapper * d_paperIdWrapper;
	struct PaperIdWrapper * paperIdWrapper;

	
public:
	virtual void MemAllo(const char* file_name);
	virtual void sort(int column);
	virtual void MemFree();

};

