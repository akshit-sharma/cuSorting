#pragma once
#include "Source.h"
#include "cuSDStruct.h"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

class CuSource : public Source
{
	
	struct PaperIdWrapper_Scheme * d_paperIdWrapper;
	struct PaperIdWrapper_Scheme * paperIdWrapper;

public:
	virtual void MemAllo(const char* file_name);
	virtual void sort(int column);
	virtual void MemFree();

};

