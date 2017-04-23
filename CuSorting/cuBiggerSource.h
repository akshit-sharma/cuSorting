#pragma once
#include "BiggerSource.h"
#include "cuRDStruct.h"

#define THREADS 512 // 2^9
#define BLOCKS 32768 // 2^15
#define NUM_VALS THREADS*BLOCKS

class CuBiggerSource : public BiggerSource
{

	int * d_int;
	int * d_xtra_int;
	int * d_ans;
	long long * d_llong;
	long long * d_xtra_llong;

	void write_file(const char * file_name, 
		ResultsDataStructure * resultsDataStructure);

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

