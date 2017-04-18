#pragma once
#include "Source.h"
#include "cuSDStruct.h"

#define NUM_BLOCK 65535
#define WID_BLOCK 1024

#define TYPE_PAPER_ID decltype(paper_id)

class CuSource : public Source
{
	
	int * d_int;
	int * d_xtra_int;

	void write_file(const char * file_name,
		SchemeDataStructure * schemeDataStructure);
	
	clock_t startTimer();
	clock_t endTimer();
	double getTimeElapsed(clock_t start, clock_t end);
	void initializeTimer(cudaEvent_t * start, cudaEvent_t * end);
	void timerEventRecord(cudaEvent_t * timer);
	void timerEventSync(cudaEvent_t * timer);
	double getTimeElapsed(cudaEvent_t start, cudaEvent_t end);

public:
	virtual double MemAllo(const char* file_name);
	virtual double preSorting();
	virtual double sort();
	virtual double postSorting();
	virtual double print_table(const char * file_name);
	virtual double MemFree();

};

