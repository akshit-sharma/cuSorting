#pragma once

#include "SchemeDataStructure.h"

struct InstitutionNameWrapper
{
	char * institution_name;
	SchemeDataStructure * classPtr;
};

struct SubjectNameWrapper
{
	char * subject_name;
	SchemeDataStructure * classPtr;
};

struct PaperIdWrapper
{
	int paper_id;
	SchemeDataStructure * classPtr;
};
