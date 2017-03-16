#pragma once

#include "ResultsDataStructure.h"

struct PaperIdWrapper {
	int paper_id;
	ResultsDataStructure * classPtr;
};

struct RollNumberWrapper {
	long long rollnumber;
	ResultsDataStructure * classPtr;
};

struct NameWrapper {
	char * name;
	ResultsDataStructure * classPtr;
};

