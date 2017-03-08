

#pragma once
#include <vector>
#include <string>
#include "Main.h"
#include "ResultsDataStructure.h"

class BiggerSource : public virtual main_class
{
private:

    std::vector<std::string> headers;

    long long * rollnumber;
    std::string * name;
	int * paper_id;

    ResultsDataStructure * resultsDataStructure;

	static int init_num;

	std::string * sorted_col_string;
	int * sorted_col_int;
	long long * sorted_col_long;

	enum type
	{
		inte, string, longe
	};

	enum type sorted_col_type;
    size_t rows;

	bool readFileToBuffer(std::string filePath, std::vector<unsigned char>& buffer);
	void swap(size_t index_1, size_t index_2);
	bool compare_isLess(std::string str1, std::string str2);
	bool compare_isMore(std::string str1, std::string str2);
	size_t partition(std::string * toSort, size_t low, size_t high);
	size_t partition(long long * toSort, size_t low, size_t high);
	size_t partition(int * toSort, size_t low, size_t high);
	void quicksort(int * toSort, size_t low, size_t high);
	void quicksort(long long * toSort, size_t low, size_t high);
	void quicksort(std::string * toSort, size_t low, size_t high);
	void shellsort(std::string* toSort, size_t low, size_t high);
	void shellsort(long long* toSort, size_t low, size_t high);
	void shellsort(int* toSort, size_t low, size_t high);
	void bubblesort(std::string* toSort, size_t low, size_t high);
	void bubblesort(long long* toSort, size_t low, size_t high);
	void bubblesort(int* toSort, size_t low, size_t high);

public:
	void MemAllo();
	void readFile(const char * file_name);
	void sort(int column);
	void print_table(const char * file_name);
	void MemFree();


};
