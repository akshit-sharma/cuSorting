#pragma once
#include "BiggerSource.h"
#include "cuRDStruct.h"

class CuBiggerSource : public BiggerSource
{
	struct PaperIdWrapper_Results * paperIdWrapper;
	struct RollNumberWrapper_Results * rollNumberWrapper;

	struct PaperIdWrapper_Results * d_paperIdWrapper;
	struct RollNumberWrapper_Results * d_rollNumberWrapper;

public:
	virtual void MemAllo(const char* file_name);
	virtual void sort(int column);
	virtual void MemFree();

};

