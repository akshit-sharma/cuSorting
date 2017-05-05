#pragma once

#ifndef H_GLOBALHEADER_H
#define H_GLOBALHEADER_H

#include<iostream>
#include<fstream>

#define FileCountMax 40
#define StatusCountMax 2
#define DIVIDENT 200		// 200 for 2.5 and 100 for 5


#ifdef _MSC_VER

#define printf_stream(stream,fixed_string,...)\
		fprintf_s(stream,fixed_string,##__VA_ARGS__)

#define fopen_stream(stream,fixed_string,permissions)\
		fopen_s(stream,fixed_string,permissions)

#else

#define printf_stream(stream,fixed_string,...)\
		fprintf(stream,fixed_string,##__VA_ARGS__)

#define fopen_stream(stream,fixed_string,permissions)\
		*stream = fopen(fixed_string,permissions)

#endif

#ifdef __INTELLISENSE__
#define __launch_bounds__(a,b)
void __syncthreads(void);
void __threadfence(void);
//void atomicAdd(int *, int);
#endif

#define MAX_DEPTH       16
#define INSERTION_SORT  32


#define SWAP(temp_var, index_1, index_2, array_name)     \
	temp_var = array_name[index_1];	                     \
	array_name[index_1] = array_name[index_2];			 \
	array_name[index_2] = temp_var;

extern const bool skip_quick_cpu;
extern const bool skip_shell_cpu;
extern const bool skip_bubble_cpu;
extern const bool skip_quick_gpu;
extern const bool skip_shell_gpu;
extern const bool skip_bubble_gpu;

extern const bool skip_input;
extern const bool skip_sorting;
extern const bool skip_check_output;

#endif


