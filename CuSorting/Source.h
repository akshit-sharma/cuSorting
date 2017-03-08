
#include <vector>
#include <string>

#include "SchemeDataStructure.h"
#include "Main.h"

#pragma once
class Source : public virtual main_class
{
private:

	std::vector <std::string> headers;

	std::string * institution_name;
	int * paper_id;
	std::string * subject_name;

    SchemeDataStructure * schemeDataStructure;

	static int init_num;

	std::string * sorted_col_string;
	int * sorted_col_int;

	enum type
	{
		inte, string
	};

	enum type sorted_col_type;

	size_t rows;

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

public:
	void MemAllo();
	void readFile(const char * file_name);
	void sort(int column);
	void print_table(const char * file_name);
	void MemFree();

};
