
#include <fstream>
#include <iomanip>
#include <string>

#include <stdio.h>

#include "Main.h"
#include "BiggerSource.h"
#include "Source.h"

#include "Test.h"

Source source;
BiggerSource bigsource;

double small_times, big_times;
double avg_read_times_small, avg_read_times_big;
double memory_alloc_time;
double sort_duration;
double avg_write_times_small, avg_write_times_big;
double memory_dealloc_time;

const char * file_name_small;
const char * file_name_big;
const char * output_file_name;

void runSort(main_class * source_obj, int value, double * timeTaken)
{

	std::clock_t start;
	double duration;

	start = std::clock();
	source_obj->MemAllo();
	memory_alloc_time = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	start = std::clock();
	if(!skip_input){
		if(value % 2 == 0)
			source_obj->readFile(file_name_small, value/2);
		else
			source_obj->readFile(file_name_big, value/2);
	}
	duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	if (value % 2 == 0)
		avg_read_times_small += duration;
	else
		avg_read_times_big += duration;

	start = std::clock();
	if(!skip_sorting)
	source_obj->sort(value/2);
	duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	sort_duration = duration;

	start = std::clock();
	if(!skip_output)
	source_obj->print_table(output_file_name);
	duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	start = std::clock();
	source_obj->MemFree();
	memory_dealloc_time = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	if (value % 2 == 0)
		avg_write_times_small += duration;
	else
		avg_write_times_big += duration;
	 
	if (value % 2 == 0)
		small_times++;
	else
		big_times++;

	*timeTaken = sort_duration;

}

int main(int argc, char ** argv)
{
	/*
	const int arraySize = 5;
	const int a[arraySize] = { 1, 2, 3, 4, 5 };
	const int b[arraySize] = { 10, 20, 30, 40, 50 };
	int c[arraySize] = { 0 };

	// Add vectors in parallel.
	cudaError_t cudaStatus = addWithCuda(c, a, b, arraySize);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "addWithCuda failed!");
		return 1;
	}

	printf("{1,2,3,4,5} + {10,20,30,40,50} = {%d,%d,%d,%d,%d}\n",
		c[0], c[1], c[2], c[3], c[4]);

	// cudaDeviceReset must be called before exiting in order for profiling and
	// tracing tools such as Nsight and Visual Profiler to show complete traces.
	cudaStatus = cudaDeviceReset();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceReset failed!");
		return 1;
	}

	return 0;
	*/

	if (argc != 4)
	{
		perror("Invalid parameter given");
		perror("Found parameter : "+argc);
		perror("argv[1], argv[2] & argv[3] not supplied");
		perror("argv[1] & argv[2] is the path of input file");
		perror("argv[3] is the path of output file");
		exit(1);
	}
	
	file_name_small = argv[1];
	file_name_big = argv[2];
	output_file_name = argv[3];

	avg_read_times_big = 0;
	avg_read_times_small = 0;
	avg_write_times_big = 0;
	avg_write_times_small = 0;

	small_times = 0;
	big_times = 0;


	printf_stream(stdout, " %10s | %10s | %10s | %10s | %10s | %10s | %10s \n",
		"technique", "memAlloc", "colSmData", "timeTaken", "memDealloc", "colBiData", "timeTaken"
			);



	main_class * source_obj = &source;
	main_class * big_source_obj = &bigsource;

	double * sort_small;
	double * sort_big;

	double f1, f2;

	f1 = 0;
	f2 = 0;

	sort_small = &f1;
	sort_big = &f2;
	
	runSort(source_obj, 2, sort_small);
	runSort(big_source_obj, 3, sort_big);
	
	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"quicksort", memory_alloc_time, "paper_id", *sort_small, memory_dealloc_time, "paper_id", *sort_big
	);

	runSort(source_obj, 4, sort_small);
	runSort(big_source_obj, 5, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"quicksort", memory_alloc_time, "subjName", *sort_small, memory_dealloc_time, "name", *sort_big
	);

	runSort(source_obj, 6, sort_small);
	runSort(big_source_obj, 7, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"quicksort", memory_alloc_time, "InstiName", *sort_small, memory_dealloc_time, "rollnum.", *sort_big
	);

	runSort(source_obj, 8, sort_small);
	runSort(big_source_obj, 9, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"shellsort", memory_alloc_time, "paper_id", *sort_small, memory_dealloc_time, "paper_id", *sort_big
	);

	runSort(source_obj, 10, sort_small);
	runSort(big_source_obj, 11, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"shellsort", memory_alloc_time, "subjName", *sort_small, memory_dealloc_time, "name", *sort_big
	);

	runSort(source_obj, 12, sort_small);
	runSort(big_source_obj, 13, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"shellsort", memory_alloc_time, "InstiName", *sort_small, memory_dealloc_time, "rollnum.", *sort_big
	);
	
	runSort(source_obj, 14, sort_small);
	runSort(big_source_obj, 15, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"bubblesort", memory_alloc_time, "paper_id", *sort_small, memory_dealloc_time, "paper_id", *sort_big
	);

	runSort(source_obj, 16, sort_small);
	runSort(big_source_obj, 17, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"bubblesort", memory_alloc_time, "subjName", *sort_small, memory_dealloc_time, "name", *sort_big
	);

	runSort(source_obj, 18, sort_small);
	runSort(big_source_obj, 19, sort_big);

	printf_stream(stdout, " %10s | %10.5lf | %10s | %10.5lf | %10.5lf | %10s | %10.5lf \n",
		"bubblesort", memory_alloc_time, "InstiName", *sort_small, memory_dealloc_time, "rollnum.", *sort_big
	);

	
	printf_stream(stdout, "\n");

	printf_stream(stdout, "Avg small file read time %lf\n", (avg_read_times_small / small_times));
	printf_stream(stdout, "Avg big file read time %lf\n", (avg_read_times_big / big_times));
	printf_stream(stdout, "Avg small file write time %lf\n", (avg_write_times_small / small_times));
	printf_stream(stdout, "Avg big file write time %lf\n", (avg_write_times_big / big_times));

	printf_stream(stdout, "\n");
	printf_stream(stdout, "\n");

	return 0;
	 

}

