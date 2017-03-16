#pragma once
#include "Source.h"
#include "cuSDStruct.h"

class CuSource : protected Source
{
	
	struct PaperIdWrapper * d_paperIdWrapper;
	struct PaperIdWrapper * paperIdWrapper;

	
public:
	virtual void MemAllo();
	virtual void sort(int column);
	virtual void MemFree();

};

