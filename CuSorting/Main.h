#pragma once

#include "GlobalHeader.h"

#define call_runsort(technique, small_number, small_col, big_number, big_col )			\
	runSort(source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "cpu", memory_alloc_time, small_col, *sort_small, memory_dealloc_time);		\
	runSort(big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		"", "result", "gpu", memory_alloc_time, big_col, *sort_small, memory_dealloc_time);

#define call_runsort_gpu(technique, small_number, small_col, big_number, big_col )			\
	runSort(cu_source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "cpu", memory_alloc_time, small_col, *sort_small, memory_dealloc_time);		\
	runSort(cu_big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf \n",				\
		"", "result", "gpu", memory_alloc_time, big_col, *sort_small, memory_dealloc_time);

#define both_call_runsort(technique, small_number, small_col, big_number, big_col )			\
	call_runsort(technique, small_number, small_col, big_number, big_col );					\
	call_runsort_gpu(technique, small_number, small_col, big_number, big_col );


class main_class
{
public:
	virtual void MemAllo(const char* file_name) = 0;
	virtual void readFile(const char * file_name, int column) = 0;
	virtual void sort(int column) = 0;
	virtual void print_table(const char * file_name) = 0;
	virtual void MemFree() = 0;
};