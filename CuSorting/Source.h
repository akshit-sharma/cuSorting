
#include <vector>
#include <string>

#include "SchemeDataStructure.h"
#include "Main.h"

#pragma once
class Source : public virtual main_class
{
private:

	std::string * sorted_col_string;
	int * sorted_col_int;

	enum type
	{
		inte, string
	};

	enum type sorted_col_type;

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

protected:
	std::vector <std::string> headers;

	static int init_num;


	int * paper_id;
	std::string * subject_name;
	std::string * institution_name;

	SchemeDataStructure * schemeDataStructure;

	int column_decide;

//	int column;

	size_t length_institution_name, length_subject_name;
	size_t maxLength_inti, maxLength_subj;

	size_t rows;

public:
	virtual void selectColumn(int column);
	virtual void MemAllo(const char* file_name);
	void readFile(const char * file_name);
	virtual void sort();
	virtual void postSorting();
	void print_table(const char * file_name);
	virtual void MemFree();
	virtual bool checkComputation();

};
