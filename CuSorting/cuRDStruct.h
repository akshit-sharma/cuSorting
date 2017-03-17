#pragma once

#include "ResultsDataStructure.h"

struct PaperIdWrapper_Results {
	int paper_id;
	ResultsDataStructure * classPtr;
};

struct RollNumberWrapper_Results {
	long long rollnumber;
	ResultsDataStructure * classPtr;
};

struct NameWrapper_Results {
	char * name;
	ResultsDataStructure * classPtr;
};

