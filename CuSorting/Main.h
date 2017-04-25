#pragma once

#include "GlobalHeader.h"

#define BoolToCheck																						\
		computationCheckAnswer?"Correct":"Wrong"			


#ifdef _MSC_VER

#define printf_stream_file(stream_1,stream_2,fixed_string,...)\
		printf_stream(stream_1,fixed_string,##__VA_ARGS__);	\
		printf_stream(stream_2,fixed_string,##__VA_ARGS__);	\
		fflush(stream_2);

#define printf_stream_file_excel(stream_1,stream_2,stream_3,fixed_string,...)	\
		printf_stream_file(stream_1,stream_2,fixed_string,##__VA_ARGS__)	\
		std::string fixedString = fixed_string;								\
		std::replace( fixedString.begin(), fixedString.end(), '|', ',');	\
		printf_stream(stream_3, fixedString.c_str(),##__VA_ARGS__);					\
		fflush(stream_3);
#else

#define printf_stream_file(stream_1,stream_2,fixed_string,...)\
		printf_stream(stream_1,fixed_string,##__VA_ARGS__);	\
		printf_stream(stream_2,fixed_string,##__VA_ARGS__);

#endif

#define call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
	if(hasCudaEnabledGPU && !(skip_gpu)){																	\
			runSort(cu_source_obj, small_number);															\
	printf_stream_file_excel(stdout, fs, database_file, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf"		\
															" | %10.5lf | %10.5lf | %10.5lf | %10u | %8s \n",	\
		technique, "scheme", "gpu", memory_alloc_time, small_col, pre_sort_duration,						\
		sort_duration, post_sort_duration, memory_dealloc_time, rowsCount, BoolToCheck);					\
	}																										\
	if(!skip_cpu){																							\
				runSort(source_obj, small_number);															\
	printf_stream_file_excel(stdout, fs, database_file, " %10s | %7s | %4s | %10.5lf | %10s |"				\
													" %10.5lf | %10.5lf | %10.5lf | %10.5lf | %10u | %8s \n",		\
		technique, "scheme", "cpu", memory_alloc_time, small_col, pre_sort_duration, sort_duration,			\
					post_sort_duration, memory_dealloc_time, rowsCount, BoolToCheck);						\
	}



#define call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
	if(hasCudaEnabledGPU && !(skip_gpu)){																	\
		runSort(cu_big_source_obj, big_number);																\
	printf_stream_file_excel(stdout, fs, database_file, " %10s | %7s | %4s | %10.5lf | %10s |"				\
														" %10.5lf | %10.5lf | %10.5lf | %10.5lf | %10u | %8s \n",	\
					technique, "result", "gpu", memory_alloc_time, big_col, pre_sort_duration,				\
					sort_duration, post_sort_duration, memory_dealloc_time, rowsCount, BoolToCheck);		\
	}																										\
	if(!skip_cpu){																							\
				runSort(big_source_obj, big_number);														\
	printf_stream_file_excel(stdout, fs, database_file, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf"		\
															" | %10.5lf | %10.5lf | %10.5lf | %10u | %8s \n",		\
		technique, "result", "cpu", memory_alloc_time, big_col, pre_sort_duration,							\
		sort_duration, post_sort_duration, memory_dealloc_time, rowsCount, BoolToCheck);					\
	}								



#define both_call_runsort_skip(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
		call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu);	\
		call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu);		



/////////////////////////////////////////////////////////////////////////////////////////////////////////
// From deviceQuery Example
/////////////////////////////////////////////////////////////////////////////////////////////////////////

#if CUDART_VERSION < 5000

// CUDA-C includes
#include <cuda.h>

// This function wraps the CUDA Driver API into a template function
template <class T>
inline void getCudaAttribute(T *attribute, CUdevice_attribute device_attribute, int device)
{
	CUresult error = cuDeviceGetAttribute(attribute, device_attribute, device);

	if (CUDA_SUCCESS != error)
	{
		fprintf(stderr, "cuSafeCallNoSync() Driver API error = %04d from file <%s>, line %i.\n",
			error, __FILE__, __LINE__);

		exit(EXIT_FAILURE);
	}
}

#endif /* CUDART_VERSION < 5000 */

/////////////////////////////////////////////////////////////////////////////////////////////////////////
// End of deviceQuery Example
/////////////////////////////////////////////////////////////////////////////////////////////////////////

bool detectCudaEnabledGPU();
extern bool hasCudaEnabledGPU;


class main_class
{
public:
	virtual void setRows(size_t size) = 0;
	virtual void selectColumn(int column) = 0;
	virtual double MemAllo(const char* file_name) = 0;
	virtual size_t getRowsCount() = 0;
	virtual double readFile(const char * file_name) = 0;
	virtual double preSorting() = 0;
	virtual double sort() = 0;
	virtual double postSorting() = 0;
	virtual double print_table(const char * file_name) = 0;
	virtual double MemFree() = 0;
	virtual bool checkComputation() = 0;
};