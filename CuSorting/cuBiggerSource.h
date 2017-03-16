#pragma once
#include "BiggerSource.h"
#include "cuRDStruct.h"

class CuBiggerSource : protected BiggerSource
{
	struct PaperIdWrapper * paperIdWrapper;
	struct RollNumberWrapper * rollNumberWrapper;

	struct PaperIdWrapper * d_paperIdWrapper;
	struct RollNumberWrapper * d_rollNumberWrapper;

public:
	virtual void MemAllo(const char* file_name);
	virtual void sort(int column);
	virtual void MemFree();

};

