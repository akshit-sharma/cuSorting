#pragma once

#ifndef H_GLOBALHEADER_H
#define H_GLOBALHEADER_H

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

extern const bool skip_quick_cpu;
extern const bool skip_shell_cpu;
extern const bool skip_bubble_cpu;

extern const bool skip_input;
extern const bool skip_sorting;
extern const bool skip_check_output;

#endif


