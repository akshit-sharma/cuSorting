#pragma once
#include "Source.h"
#include "cuSDStruct.h"

class CuSource : protected Source
{

	int * d_paper_id;
	char * d_institution_name;
	char * d_subject_name;

	char * h_institution_name;
	char * h_subject_name;

	SchemeDataStructure * d_schemeDataStructure;

	struct PaperIdWrapper * paperIdWrapper;

	
public:
	virtual void MemAllo();
	virtual void sort(int column);
	virtual void MemFree();

};

