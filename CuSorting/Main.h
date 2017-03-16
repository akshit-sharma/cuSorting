#pragma once

#include "GlobalHeader.h"

#define call_runsort(technique, small_number, small_col, big_number, big_col )			\
	runSort(source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		technique, memory_alloc_time, small_col, *sort_small, memory_dealloc_time);		\
	runSort(big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		"", memory_alloc_time, big_col, *sort_small, memory_dealloc_time);



class main_class
{
public:
	virtual void MemAllo() = 0;
	virtual void readFile(const char * file_name, int column) = 0;
	virtual void sort(int column) = 0;
	virtual void print_table(const char * file_name) = 0;
	virtual void MemFree() = 0;
};