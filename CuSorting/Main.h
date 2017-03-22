#pragma once

#include "GlobalHeader.h"

#define call_runsort(technique, small_number, small_col, big_number, big_col )			\
	runSort(source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "cpu", memory_alloc_time, small_col, *sort_small, post_sort_duration, memory_dealloc_time);		\
	runSort(big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		"", "result", "cpu", memory_alloc_time, big_col, *sort_small, post_sort_duration, memory_dealloc_time);

#define call_runsort_gpu(technique, small_number, small_col, big_number, big_col )			\
	runSort(cu_source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "gpu", memory_alloc_time, small_col, *sort_small, post_sort_duration, memory_dealloc_time);		\
	runSort(cu_big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		"", "result", "gpu", memory_alloc_time, big_col, *sort_small, post_sort_duration, memory_dealloc_time);

#define call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu )			\
	if(!skip_cpu){																					\
				runSort(source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "cpu", memory_alloc_time, small_col, *sort_small, post_sort_duration, memory_dealloc_time);		\
	}																											\
	runSort(cu_source_obj, small_number, sort_small);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "scheme", "gpu", memory_alloc_time, small_col, *sort_small, post_sort_duration, memory_dealloc_time);		

#define call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu )			\
	if(!skip_cpu){																					\
				runSort(big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "result", "cpu", memory_alloc_time, big_col, *sort_small, post_sort_duration, memory_dealloc_time);		\
	}																											\
	runSort(cu_big_source_obj, big_number, sort_big);										\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf \n",				\
		technique, "result", "gpu", memory_alloc_time, big_col, *sort_small, post_sort_duration, memory_dealloc_time);


#define both_call_runsort(technique, small_number, small_col, big_number, big_col )			\
	call_runsort(technique, small_number, small_col, big_number, big_col );					\
	call_runsort_gpu(technique, small_number, small_col, big_number, big_col );

#define both_call_runsort_skip(technique, small_number, small_col, big_number, big_col, skip_cpu)\
	call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu );			\
	call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu );


class main_class
{
public:
	virtual void selectColumn(int column) = 0;
	virtual void MemAllo(const char* file_name) = 0;
	virtual void readFile(const char * file_name) = 0;
	virtual void sort() = 0;
	virtual void postSorting() = 0;
	virtual void print_table(const char * file_name) = 0;
	virtual void MemFree() = 0;
	virtual bool checkComputation() = 0;
};