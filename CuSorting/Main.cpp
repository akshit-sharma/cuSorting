
#include <fstream>
#include <iomanip>
#include <string>
#include <algorithm> 

#include <stdio.h>

#include <cuda_runtime.h>

#include "Main.h"
#include "Source.h"
#include "BiggerSource.h"
#include "cuSource.h"
#include "cuBiggerSource.h"

#include "GPU_Sorting_Functions.cuh"

Source source;
BiggerSource bigsource;

CuSource cuSource;
CuBiggerSource cuBiggerSource;

FILE * fs;
FILE * status_file;
FILE * database_file;

int runFileCount;
int runStatusCount;

double small_times, big_times;
double avg_read_times_small, avg_read_times_big;
double memory_alloc_time;
double pre_sort_duration;
double sort_duration;
double post_sort_duration;
double check_sort_calc;
double memory_dealloc_time;

bool computationCheckAnswer;

const char * file_name_small;
const char * file_name_big;
const char * output_file_name;

void runSort(main_class * source_obj, int value)
{
		
	source_obj->selectColumn(value / 2);

	source_obj->setRows(runFileCount*5);

	if (value % 2 == 0)
		memory_alloc_time = source_obj->MemAllo(file_name_small);
	else
		memory_alloc_time = source_obj->MemAllo(file_name_big);
	
	if(!skip_input){
		if(value % 2 == 0)
			avg_read_times_small += source_obj->readFile(file_name_small);
		else
			avg_read_times_big += source_obj->readFile(file_name_big);
	}
	
	pre_sort_duration = source_obj->preSorting();
	
	if(!skip_sorting)
		sort_duration = source_obj->sort();
	
	post_sort_duration = source_obj->postSorting();
	
	if (!skip_check_output)
		computationCheckAnswer = source_obj->checkComputation();
	
	if(!computationCheckAnswer)
		source_obj->print_table(output_file_name);

	memory_dealloc_time = source_obj->MemFree();
	 
	if (value % 2 == 0)
		small_times++;
	else
		big_times++;
	
}

int main(int argc, char ** argv)
{

	if (argc != 5)
	{
		perror("Invalid parameter given");
		perror("Found parameter : " + argc);
		perror("argv[1], argv[2], argv[3] & argv[4] not supplied");
		perror("argv[1] & argv[2] is the path of input file");
		perror("argv[3] is the path of output file");
		perror("argv[4] is the path of output folder");
		exit(1);
	}

	std::string fileName;

	runFileCount = -1;
	runStatusCount = -1;

	fileName = std::string(argv[4]);
	fileName += "Status.txt";
	status_file = fopen(fileName.c_str(), "r");

	fscanf(status_file, "%d", &runFileCount);
	fscanf(status_file, "%d", &runStatusCount);
	fclose(status_file);

	if (runFileCount > 39)
	{
		exit(127);
	}
	
	fileName = std::string(argv[4]);
	fileName += "ProgramOutput-";
	fileName += std::to_string(runFileCount);
	fileName += "-";
	fileName += std::to_string(runStatusCount);
	fileName += ".txt";
	fs = fopen(fileName.c_str(), "w");

	bool hasCudaEnabledGPU = detectCudaEnabledGPU();

	file_name_small = argv[1];
	file_name_big = argv[2];
	output_file_name = argv[3];

	avg_read_times_big = 0;
	avg_read_times_small = 0;

	small_times = 0;
	big_times = 0;


	
	main_class * source_obj = &source;
	main_class * big_source_obj = &bigsource;

	main_class * cu_source_obj = &cuSource;
	main_class * cu_big_source_obj = &cuBiggerSource;

	double * sort_small;
	double * sort_big;

	double f1, f2;

	f1 = 0;
	f2 = 0;

	sort_small = &f1;
	sort_big = &f2;

	fileName = std::string(argv[4]);
	fileName += "OutputDataset";
	fileName += ".csv";
	database_file = fopen(fileName.c_str(), "a");

	if (runFileCount == 0 && runStatusCount == 0)
	{
		printf_stream_file_excel(stdout, fs, database_file, " %10s | %7s | %4s | %10s | %10s | %10s | %10s | %10s | %10s | %8s \n",
			"technique", "dataset", "ALU", "memAlloc", "colData", "PreEvent", "timeTaken", "PostEvent", "memDealloc", "Correct?"
		);
	}
	else
	{
		printf_stream_file(stdout, fs, " %10s | %7s | %4s | %10s | %10s | %10s | %10s | %10s | %10s | %8s \n",
			"technique", "dataset", "ALU", "memAlloc", "colData", "PreEvent", "timeTaken", "PostEvent", "memDealloc", "Correct?"
		);
	}
	
	switch (runStatusCount)
	{
	case 0:		
		runFileCount++;
		call_runsort_scheme("quicksort", 2, "paper_id", 3, "paper_id", skip_quick_cpu, skip_quick_gpu);
		break;
	case 1:
		call_runsort_results("quicksort", 2, "paper_id", 3, "paper_id", skip_quick_cpu, skip_quick_gpu);
		break;
	case 2:
		call_runsort_results("quicksort", 6, "InstiName", 7, "rollnum.", skip_quick_cpu, skip_quick_gpu);
		break;
	case 3:
		call_runsort_scheme("bitonic", 8, "paper_id", 9, "paper_id", skip_shell_cpu, skip_shell_gpu);
		break;
	case 4:
		call_runsort_results("bitonic", 8, "paper_id", 9, "paper_id", skip_shell_cpu, skip_shell_gpu);
		break;
	case 5:
		call_runsort_results("bitonic", 12, "InstiName", 13, "rollnum.", skip_shell_cpu, skip_shell_gpu);
		break;
	default:
		break;
	}

	fflush(database_file);
	fclose(database_file);

	runStatusCount++;

	if (runStatusCount > 5)
		runStatusCount = 0;


//	both_call_runsort_skip("quicksort", 2, "paper_id", 3, "paper_id", skip_quick_cpu, skip_quick_gpu);
//	call_runsort_results("quicksort", 6, "InstiName", 7, "rollnum.", skip_quick_cpu, skip_quick_gpu);

//	both_call_runsort_skip("bitonic", 8, "paper_id", 9, "paper_id", skip_shell_cpu, skip_shell_gpu);
//	call_runsort_results("bitonic", 12, "InstiName", 13, "rollnum.", skip_shell_cpu, skip_shell_gpu);

//	call_runsort_scheme("bubblesort", 14, "paper_id", 15, "paper_id", skip_bubble_cpu, skip_bubble_gpu);
//	both_call_runsort_skip("bubblesort", 14, "paper_id", 15, "paper_id", skip_bubble_cpu, skip_bubble_gpu);
//	call_runsort_results("bubblesort", 18, "InstiName", 19, "rollnum.", skip_bubble_cpu, skip_bubble_gpu);

	printf_stream_file(stdout, fs, "\n");

	fileName = std::string(argv[4]);
	fileName += "Status.txt";
	status_file = fopen(fileName.c_str(), "w");

	printf_stream(status_file, "%d %d", runFileCount, runStatusCount);
	fflush(status_file);
	fclose(status_file);

	printf_stream_file(stdout, fs, "Avg small file read time %lf\n", (avg_read_times_small / small_times));
	printf_stream_file(stdout, fs, "Avg big file read time %lf\n", (avg_read_times_big / big_times));

	printf_stream_file(stdout, fs, "\n");
	printf_stream_file(stdout, fs, "\n");

	fclose(fs);

	return 0;
	 

}

bool detectCudaEnabledGPU()
{

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// From deviceQuery Example
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	int deviceCount = 0;
	cudaError_t error_id = cudaGetDeviceCount(&deviceCount);

	if (error_id != cudaSuccess)
	{
		printf_stream_file(stdout, fs, "cudaGetDeviceCount returned %d\n-> %s\n", (int)error_id, cudaGetErrorString(error_id));
		printf_stream_file(stdout, fs, "Result = FAIL\n");
		printf_stream_file(stdout, fs, "There are no available device(s) that support CUDA\n");
		return false;
	}

	// This function call returns 0 if there are no CUDA capable devices.
	if (deviceCount == 0)
	{
		printf_stream_file(stdout, fs, "There are no available device(s) that support CUDA\n");
		return false;
	}
	else
	{
		printf_stream_file(stdout, fs, "Detected %d CUDA Capable device(s)\n", deviceCount);
		
		int dev = 0, driverVersion = 0, runtimeVersion = 0;

		gpuErrchk(
		cudaSetDevice(dev));
		cudaDeviceProp deviceProp;
		gpuErrchk(
		cudaGetDeviceProperties(&deviceProp, dev));

		printf_stream_file(stdout, fs, "\nDevice %d: \"%s\"\n", dev, deviceProp.name);

		// Console log
		gpuErrchk(
		cudaDriverGetVersion(&driverVersion));
		gpuErrchk(
		cudaRuntimeGetVersion(&runtimeVersion));
		printf_stream_file(stdout, fs, "  CUDA Driver Version / Runtime Version          %d.%d / %d.%d\n", driverVersion / 1000, (driverVersion % 100) / 10, runtimeVersion / 1000, (runtimeVersion % 100) / 10);
		printf_stream_file(stdout, fs, "  CUDA Capability Major/Minor version number:    %d.%d\n", deviceProp.major, deviceProp.minor);

		printf_stream_file(stdout, fs, "\n\n");

	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	// End of deviceQuery Example
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	return true;

}


