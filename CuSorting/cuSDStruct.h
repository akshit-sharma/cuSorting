#pragma once

#include "SchemeDataStructure.h"

struct InstitutionNameWrapper_Scheme
{
	char * institution_name;
	SchemeDataStructure * classPtr;
};

struct SubjectNameWrapper_Scheme
{
	char * subject_name;
	SchemeDataStructure * classPtr;
};

struct PaperIdWrapper_Scheme
{
	int padding;
	int paper_id;
	SchemeDataStructure * classPtr;
};
