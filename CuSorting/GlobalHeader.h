#pragma once

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


