#pragma once

#include "GlobalHeader.h"

#define BoolToCheck																						\
		computationCheckAnswer?"Correct":"Wrong"																									

#define call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
	if(!skip_cpu){																							\
				runSort(source_obj, small_number, sort_small);												\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf | %8s \n",		\
		technique, "scheme", "cpu", memory_alloc_time, small_col, *sort_small, post_sort_duration			\
					, memory_dealloc_time, BoolToCheck);													\
	}																										\
	if(hasCudaEnabledGPU && !(skip_gpu)){																	\
			runSort(cu_source_obj, small_number, sort_small);												\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf | %8s \n",		\
		technique, "scheme", "gpu", memory_alloc_time, small_col, *sort_small, post_sort_duration,			\
		memory_dealloc_time, BoolToCheck);																	\
	}

#define call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
	if(!skip_cpu){																							\
				runSort(big_source_obj, big_number, sort_big);												\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s | %10.5lf | %10.5lf | %10.5lf | %8s \n",		\
		technique, "result", "cpu", memory_alloc_time, big_col, *sort_small, post_sort_duration,			\
					memory_dealloc_time, BoolToCheck);														\
	}																										\
	if(hasCudaEnabledGPU && !(skip_gpu)){																	\
		runSort(cu_big_source_obj, big_number, sort_big);													\
	printf_stream(stdout, " %10s | %7s | %4s | %10.5lf | %10s |"											\
														" %10.5lf | %10.5lf | %10.5lf | %8s \n",			\
					technique, "result", "gpu", memory_alloc_time,											\
					big_col, *sort_small, post_sort_duration, memory_dealloc_time, BoolToCheck);			\
	}


#define both_call_runsort_skip(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu)	\
		call_runsort_scheme(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu);	\
//		call_runsort_results(technique, small_number, small_col, big_number, big_col, skip_cpu, skip_gpu);		



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
	virtual void selectColumn(int column) = 0;
	virtual void MemAllo(const char* file_name) = 0;
	virtual void readFile(const char * file_name) = 0;
	virtual void preSorting() = 0;
	virtual void sort() = 0;
	virtual void postSorting() = 0;
	virtual void print_table(const char * file_name) = 0;
	virtual void MemFree() = 0;
	virtual bool checkComputation() = 0;
};