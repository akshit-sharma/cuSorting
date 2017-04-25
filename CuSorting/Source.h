
#include <vector>
#include <string>

#include "SchemeDataStructure.h"
#include "Main.h"

#include "time.h"

#define THREADS 512 // 2^9
#define BLOCKS 32768 // 2^15
#define NUM_VALS THREADS*BLOCKS

#pragma once
class Source : public virtual main_class
{
private:

	size_t getFileLines(const char* file_name);
	bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	void swap(const size_t index_1, const size_t index_2);
	bool compare_isLess(std::string str1, std::string str2);
	bool compare_isMore(std::string str1, std::string str2);
	void quicksort(int * toSort, size_t low, size_t high);
	void quicksort(std::string* toSort, size_t low, size_t high);
	size_t partition(int * toSort, size_t low, size_t high);
	size_t partition(std::string* toSort, size_t low, size_t high);
	void shellsort(std::string* toSort, size_t low, size_t high);
	void shellsort(int* toSort, size_t low, size_t high);
	void bubblesort(std::string* toSort, size_t low, size_t high);
	void bubblesort(int* toSort, size_t low, size_t high);
	void compAndSwap(int* a, int i, int j, int dir);
	void bitonicMerge(int* a, int low, int cnt, int dir);
	void bitonicSort(int* a, int low, int cnt, int dir);

protected:

	std::string * sorted_col_string;
	int * sorted_col_int;

	static int init_num;

	enum type
	{
		inte, string
	};

	enum type sorted_col_type;

	int * paper_id;
	std::string * subject_name;
	std::string * institution_name;

	int column_decide;

	size_t length_institution_name, length_subject_name;
	size_t maxLength_inti, maxLength_subj;

	size_t rows;
	size_t max2Rows;

	clock_t startTimer();
	clock_t endTimer();
	double getTimeElapsed(clock_t start, clock_t end);

public:
	virtual void setRows(size_t size);
	virtual void selectColumn(int column);
	virtual double MemAllo(const char* file_name);
	virtual size_t getRowsCount();
	virtual double readFile(const char * file_name);
	virtual double preSorting();
	virtual double sort();
	virtual double postSorting();
	virtual double print_table(const char * file_name);
	virtual double MemFree();
	virtual bool checkComputation();

};
