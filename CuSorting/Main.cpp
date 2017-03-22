
#include <fstream>
#include <iomanip>
#include <string>

#include <stdio.h>

#include "Main.h"
#include "Source.h"
#include "BiggerSource.h"
#include "cuSource.h"
#include "cuBiggerSource.h"

Source source;
BiggerSource bigsource;

CuSource cuSource;
CuBiggerSource cuBiggerSource;

double small_times, big_times;
double avg_read_times_small, avg_read_times_big;
double memory_alloc_time;
double sort_duration;
double post_sort_duration;
double check_sort_calc;
double memory_dealloc_time;

const char * file_name_small;
const char * file_name_big;
const char * output_file_name;

void runSort(main_class * source_obj, int value, double * timeTaken)
{

	std::clock_t start;
	double duration;

	source_obj->selectColumn(value / 2);

	start = std::clock();
	if (value % 2 == 0)
		source_obj->MemAllo(file_name_small);
	else
		source_obj->MemAllo(file_name_big);
	memory_alloc_time = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	start = std::clock();
	if(!skip_input){
		if(value % 2 == 0)
			source_obj->readFile(file_name_small);
		else
			source_obj->readFile(file_name_big);
	}
	duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	if (value % 2 == 0)
		avg_read_times_small += duration;
	else
		avg_read_times_big += duration;

	start = std::clock();
	if(!skip_sorting)
	source_obj->sort();
	duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	sort_duration = duration;

	start = std::clock();
	source_obj->postSorting();
	post_sort_duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	
	start = std::clock();
	if (!skip_check_output)
		source_obj->checkComputation();
	post_sort_duration = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;

	start = std::clock();
	source_obj->MemFree();
	memory_dealloc_time = (std::clock() - start) / static_cast<double> CLOCKS_PER_SEC;
	 
	if (value % 2 == 0)
		small_times++;
	else
		big_times++;

	*timeTaken = sort_duration;

}

int main(int argc, char ** argv)
{

	if (argc != 4)
	{
		perror("Invalid parameter given");
		perror("Found parameter : " + argc);
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


	small_times = 0;
	big_times = 0;


	printf_stream(stdout, " %10s | %7s | %4s | %10s | %10s | %10s | %10s | %10s \n",
		"technique", "dataset", "ALU", "memAlloc", "colData", "timeTaken", "PostEvent", "memDealloc" 
	);



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

	both_call_runsort_skip("quicksort", 2, "paper_id", 3, "paper_id", skip_quick_cpu);
	both_call_runsort_skip("quicksort", 4, "subjName", 5, "name", skip_quick_cpu);
	both_call_runsort_skip("quicksort", 6, "InstiName", 7, "rollnum.", skip_quick_cpu);
	
	both_call_runsort_skip("shellsort", 8, "paper_id", 9, "paper_id", skip_shell_cpu);
	both_call_runsort_skip("shellsort", 10, "subjName", 11, "name", skip_shell_cpu);
	both_call_runsort_skip("shellsort", 12, "InstiName", 13, "rollnum.", skip_shell_cpu);
	
	both_call_runsort_skip("bubblesort", 14, "paper_id", 15, "paper_id", skip_bubble_cpu);
	both_call_runsort_skip("bubblesort", 16, "subjName", 17, "name", skip_bubble_cpu);
	both_call_runsort_skip("bubblesort", 18, "InstiName", 19, "rollnum.", skip_bubble_cpu);
	
	printf_stream(stdout, "\n");

	printf_stream(stdout, "Avg small file read time %lf\n", (avg_read_times_small / small_times));
	printf_stream(stdout, "Avg big file read time %lf\n", (avg_read_times_big / big_times));

	printf_stream(stdout, "\n");
	printf_stream(stdout, "\n");

	return 0;
	 

}

