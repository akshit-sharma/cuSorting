#include "BiggerSource.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>

int BiggerSource::init_num = 0;

double BiggerSource::preSorting()
{
	clock_t start;
	size_t index;
	start = startTimer();

	switch (column_decide % 3)
	{

	case 0:
		sorted_col_long = rollnumber;
		sorted_col_type = longe;

		if (column_decide % 3 == 0)
			for (index = rows; index < max2Rows; index++)
				this->rollnumber[index] = LONG_MAX;

		break;
	case 1:
		sorted_col_int = paper_id;
		sorted_col_type = inte;

		if (column_decide % 3 == 1)
			for (index = rows; index < max2Rows; index++)
				this->paper_id[index] = INT_MAX;

		break;
	case 2:
		sorted_col_string = name;
		sorted_col_type = string;
		break;

	default:
		break;
	}

	return getTimeElapsed(start, endTimer());
}

double BiggerSource::sort()
{
	clock_t start;
	start = startTimer();

	switch (column_decide)
	{
	case 1:
		quicksort(paper_id, 0, rows - 1);
		break;
	case 2:
		quicksort(name, 0, rows - 1);
		break;
	case 3:
		quicksort(rollnumber, 0, rows - 1);
		break;
	case 4:
		bitonicSort(paper_id, 0, max2Rows, 1);
		break;
	case 5:
		shellsort(name, 0, rows - 1);
		break;
	case 6:
		bitonicSort(rollnumber, 0, max2Rows, 1);
		break;
	case 7:
		bubblesort(paper_id, 0, rows - 1);
		break;
	case 8:
		bubblesort(name, 0, rows - 1);
		break;
	case 9:
		bubblesort(rollnumber, 0, rows - 1);
		break;
	default:
		break;
	}

	return getTimeElapsed(start, endTimer());
}

double BiggerSource::postSorting()
{
	clock_t start;
	start = startTimer();

	return getTimeElapsed(start, endTimer());
}

size_t BiggerSource::getFileLines(const char* file_name)
{
	size_t lines = -1;
	char line[513];

	std::ifstream file(file_name,
		std::ios::binary | std::ios::in);

	if (file.fail())
	{
		perror("Error in opening line");
		perror(file_name);
		exit(2);
	}


	while (file.getline(line, 512, '\n')) {
		lines++;
	}

	return lines;

}

double BiggerSource::readFile(const char* file_name)
{
	clock_t start;
	start = startTimer();

    std::vector<unsigned char> buffer;
    char temp_var[128];
    char line[513];
    int index;
    size_t line_number;
    int category;

	int paper_id;
	long long rollnumber;
	std::string name;

	bool overpassed_name = NULL;
	
    std::ifstream file(file_name,
        std::ios::binary | std::ios::in);

    if(file.fail())
    {
        perror("Error in opening line");
        perror(file_name);
        exit(2);
    }

    line_number = 0;

    while(file.getline(line, 512, '\n')){
        category = 0;
        index = 0;

		if (line_number >= rows)
			break;

        for(char * buffer_iter = line;
            *buffer_iter != '\0'; ++buffer_iter){
                if(*buffer_iter == '\n')
                {
                    line_number++;
                    index = 0;
                    continue;
                }

            if(line_number>=rows)
                break;

                if(line_number == 0)
                {
                    if(*buffer_iter == ',' || *(buffer_iter+1)=='\0')
                    {
                        continue;
                    }
                }

                if(*buffer_iter == ',' || (*(buffer_iter+1) == '\0' && line_number!=0)){
                    if(*buffer_iter == ',')
                        temp_var[index] = '\0';
                    else{
                        temp_var[index++] = *buffer_iter;
                        temp_var[index] = '\0';
                    }

                switch(category)
                    {
					case 9: //rollnumber
                        rollnumber = (atoll(temp_var));
                        break;
                    case 10: //name
						name = std::string(temp_var);
                        break;
					case 13:
						paper_id = atoi(temp_var);
						break;
                    default:
                        break;
                    }
                    index = 0;
                    ++category;
                    category %= 18;
                }
                else
                {
                    temp_var[index++] = *buffer_iter;
                }

            }

            if(line_number!=0){

				if(column_decide%3==0)
					this->rollnumber[line_number-1] = rollnumber;

				if (column_decide%3 == 1)
					this->paper_id[line_number - 1] = paper_id;

				if(column_decide%3==2)
					this->name[line_number-1] = std::string(name);

            }

            line_number++;

    }


    file.close();


	return getTimeElapsed(start, endTimer());
}

bool BiggerSource::readFileToBuffer(std::string filePath,
    std::vector<unsigned char>& buffer)
{

    std::ifstream file(filePath,
        std::ios::binary | std::ios::in);
    if(file.fail())
    {
        perror("Error in opening line");
        perror(filePath.c_str());
        return false;
    }

    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::end);

    buffer.resize(fileSize);
    file.seekg(0, std::ios::beg);
    file.read((char *)&(buffer[0]), fileSize);
    file.close();

    return true;

}

double BiggerSource::print_table(const char * file_name)
{
	clock_t start;
	start = startTimer();

	FILE * single_col_file;
	std::string sorted_file_name(file_name);

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_big_");

	sorted_file_name += std::to_string(init_num);
	sorted_file_name += ".csv";

	fopen_stream(&single_col_file, sorted_file_name.c_str(), "w");
	
    struct ResultsDSHolder resultsDSHolder;

    for(size_t i=0; i < rows; i++){

	    switch (sorted_col_type)
	    {
		case inte:
			printf_stream(single_col_file, "%d\n", sorted_col_int[i]);
			break;
		case string:
			printf_stream(single_col_file, "%s\n", sorted_col_string[i].c_str());
			break;
		case longe:
			printf_stream(single_col_file, "%lld\n", sorted_col_long[i]);
			break;
	    }

    }

	fclose(single_col_file);

	return getTimeElapsed(start, endTimer());
}

void BiggerSource::selectColumn(int column)
{
	this->column_decide = column;
	this->rows = 0;
}

void BiggerSource::setRows(size_t size)
{
	this->rows = size;
}

double BiggerSource::MemAllo(const char* file_name)
{
	clock_t start;
	start = startTimer();

    size_t colmns = 18;


	if (rows == 0)
		rows = getFileLines(file_name);
	else {
		size_t temp;
		temp = rows;
		rows = getFileLines(file_name);
		rows = (rows * temp) / 200;
	}
	
	size_t temp_rows = rows;
	size_t targetlevel = 0;
	while (temp_rows >>= 1) ++targetlevel;

	++targetlevel;
	max2Rows = 1 << targetlevel;

	//printf_stream(stdout, "Value is %llu and %llu", rows, max2Rows);

	paper_id = new int[max2Rows];
    rollnumber = new long long[max2Rows];
    name = new std::string[rows];

	length_name = 0;
	maxLength_name = 0;

	init_num++;

	return getTimeElapsed(start, endTimer());
}

double BiggerSource::MemFree()
{
	clock_t start;
	start = startTimer();
	
	delete [] paper_id;
    delete [] rollnumber;
    delete [] name;

	return getTimeElapsed(start, endTimer());
}

void BiggerSource::shellsort(std::string * toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;

	high++;
	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j < high; j++) {
			for (k = j - i; k >= 0 &&
				compare_isMore(toSort[k], toSort[k + i]); k = k - i)
			{
				if (compare_isLess(toSort[k], toSort[k + i]))
					break;
				else
					swap(k, k + i);
			}
		}

}

void BiggerSource::shellsort(long long * toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;

	high++;
	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j<high; j++)
			for (k = j - i; k >= 0 &&
				toSort[k] > toSort[k + i]; k = k - i)
			{
				if (toSort[k] < toSort[k + i])
					break;
				else
					swap(k, k + i);
			}

}

void BiggerSource::shellsort(int * toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;
	
	high++;
	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j<high; j++)
			for (k = j - i; k >= 0 &&
				toSort[k] > toSort[k + i]; k = k - i)
			{
				if (toSort[k] < toSort[k + i])
					break;
				else
					swap(k, k + i);
			}

}

void BiggerSource::bubblesort(std::string * toSort, size_t low, size_t high)
{

	size_t i, j;
	bool anySwap = false;

	for (i = high; i > low; i--) {
		anySwap = false;
		for (j = low; j < i; j++)
		{
			if (compare_isMore(toSort[j], toSort[j + 1]))
			{
				swap(j, j + 1);
				anySwap = true;
			}
			else {
				continue;
			}
		}
		if (!anySwap)
			break;
	}

}

void BiggerSource::bubblesort(long long * toSort, size_t low, size_t high)
{

	size_t i, j;
	bool anySwap = false;

	for (i = high; i > low; i--) {
		anySwap = false;
		for (j = low; j < i; j++)
		{
			if (toSort[j] <= toSort[j + 1])
				continue;
			else {
				swap(j, j + 1);
				anySwap = true;
			}
		}
		if (!anySwap)
			break;
	}

}

void BiggerSource::bubblesort(int * toSort, size_t low, size_t high)
{

	size_t i, j;
	bool anySwap = false;

	for (i = high; i > low; i--) {
		anySwap = false;
		for (j = low; j < i; j++)
		{
			if (toSort[j] <= toSort[j + 1])
				continue;
			else {
				swap(j, j + 1);
				anySwap = true;
			}
		}
		if (!anySwap)
			break;
	}

}

void BiggerSource::quicksort(std::string * toSort, size_t low, size_t high)
{
	std::stack<size_t> mini_stack;

	mini_stack.push(low);
	mini_stack.push(high);

	while (mini_stack.size() > 0) {
		size_t low;
		size_t high;

		high = mini_stack.top();
		mini_stack.pop();
		low = mini_stack.top();
		mini_stack.pop();

		if (low < high)
		{
			size_t part_index = partition(toSort, low, high);

			if (low < part_index - 1 && part_index != 0)
			{
				mini_stack.push(low);
				mini_stack.push(part_index - 1);
			}

			if (part_index + 1 < high)
			{
				mini_stack.push(part_index + 1);
				mini_stack.push(high);
			}

		}
	}
}

void BiggerSource::quicksort(long long * toSort, size_t low, size_t high)
{
	std::stack<size_t> mini_stack;

	mini_stack.push(low);
	mini_stack.push(high);

	while (mini_stack.size() > 0) {
		size_t low;
		size_t high;

		high = mini_stack.top();
		mini_stack.pop();
		low = mini_stack.top();
		mini_stack.pop();

		if (low < high)
		{
			size_t part_index = partition(toSort, low, high);

			if (low < part_index - 1 && part_index != 0)
			{
				mini_stack.push(low);
				mini_stack.push(part_index - 1);
			}

			if (part_index + 1 < high)
			{
				mini_stack.push(part_index + 1);
				mini_stack.push(high);
			}
		}
	}
}

void BiggerSource::quicksort(int * toSort, size_t low, size_t high)
{

	std::stack<size_t> mini_stack;

	mini_stack.push(low);
	mini_stack.push(high);

	while (mini_stack.size() > 0) {
		size_t low;
		size_t high;

		high = mini_stack.top();
		mini_stack.pop();
		low = mini_stack.top();
		mini_stack.pop();

		if (low < high)
		{
			size_t part_index = partition(toSort, low, high);

			if (low < part_index - 1 && part_index != 0)
			{
				mini_stack.push(low);
				mini_stack.push(part_index - 1);
			}

			if (part_index + 1 < high)
			{
				mini_stack.push(part_index + 1);
				mini_stack.push(high);
			}
		}
	}
}

size_t BiggerSource::partition(std::string* toSort, size_t low, size_t high)
{
	std::string pivot = toSort[high];

	size_t i = (low - 1);

	for (size_t j = low; j <= high - 1; j++)
	{
		if (compare_isLess(toSort[j],pivot))
		{
			i++;
			if (i != j)
				swap(i, j);
		}
	}

	if (i + 1 != high)
		swap(i + 1, high);

	return (i + 1);
}

size_t BiggerSource::partition(int * toSort, size_t low, size_t high)
{
	int pivot = toSort[high];


	size_t i = (low - 1);

	for (size_t j = low; j <= high - 1; j++)
	{
		if (toSort[j] <= pivot)
		{
			i++;
			if (i != j)
				swap(i, j);
		}
	}

	if (i + 1 != high)
		swap(i + 1, high);

	return (i + 1);
}

size_t BiggerSource::partition(long long * toSort, size_t low, size_t high)
{
	long long pivot = toSort[high];


	size_t i = (low - 1);

	for (size_t j = low; j <= high - 1; j++)
	{
		if (toSort[j] <= pivot)
		{
			i++;
			if (i != j)
				swap(i, j);
		}
	}

	if (i + 1 != high)
		swap(i + 1, high);

	return (i + 1);
}

void BiggerSource::swap(size_t index_1, size_t index_2)
{

    int temp_int;
    long long temp_long;
	std::string t_string;
    ResultsDataStructure t_resultsDataStructure;

	switch (column_decide%3)
	{
	case 0:
		SWAP(temp_long, index_1, index_2, rollnumber);
		break;
	case 1:
		SWAP(temp_int, index_1, index_2, paper_id);
		break;
	case 2:
		SWAP(t_string, index_1, index_2, name);
		break;
	}

}

bool BiggerSource::compare_isLess(std::string str1, std::string str2)
{
	size_t i;
	size_t min_i;
	i = 0;

	min_i = std::min(str1.length(), str2.length());

	while (i<min_i)
	{
		if (str1[i]<str2[i])
		{
			return true;
		}
		else if (str1[i]>str2[i])
		{
			return false;
		}
		++i;
	}

	if (str1.length() < str2.length())
		return true;

	return false;

}

bool BiggerSource::compare_isMore(std::string str1, std::string str2)
{
	size_t i;
	size_t min_i;
	i = 0;

	min_i = std::min(str1.length(), str2.length());

	while (i<min_i)
	{
		if (str1[i]<str2[i])
		{
			return false;
		}
		else if (str1[i]>str2[i])
		{
			return true;
		}
		++i;
	}

	if (str1.length() > str2.length())
		return true;

	return false;

}


bool BiggerSource::checkComputation() 
{
	int paper_id_old, paper_id_new;
	long long rollnumber_old, rollnumber_new;
	std::string name_old, name_new;

	paper_id_old = INT_MIN;
	rollnumber_old = INT_MIN;
	name_old = "";

	for (size_t i = 0; i < rows; i++) {

		switch (column_decide%3)
		{
		case 0:
			rollnumber_new = rollnumber[i];
			if (rollnumber_old > rollnumber_new)
				return false;
			rollnumber_old = rollnumber_new;
			break;
		case 1:
			paper_id_new = paper_id[i];
			if (paper_id_old > paper_id_new)
				return false;
			paper_id_old = paper_id_new;
			break;
		case 2:
			name_new = name[i];
			if (compare_isMore(name_old,name_new))
				return false;
			name_old = name_new;
			break;
		default:
			break;
		}

	}

	return true;

}

std::clock_t BiggerSource::startTimer()
{
	return std::clock();
}


std::clock_t BiggerSource::endTimer()
{
	return std::clock();
}

double BiggerSource::getTimeElapsed(std::clock_t start, std::clock_t end)
{
	return (end - start) / static_cast<double>(CLOCKS_PER_SEC);
}

void BiggerSource::compAndSwap(int* a, int i, int j, int dir)
{
	if (dir == (a[i] > a[j]))
		swap(i, j);
}

void BiggerSource::bitonicMerge(int* a, int low, int cnt, int dir)
{
	if (cnt>1)
	{
		int k = cnt / 2;
		for (int i = low; i<low + k; i++)
			compAndSwap(a, i, i + k, dir);
		bitonicMerge(a, low, k, dir);
		bitonicMerge(a, low + k, k, dir);
	}
}

void BiggerSource::bitonicSort(int* a, int low, int cnt, int dir)
{
	if (cnt>1)
	{
		int k = cnt / 2;

		bitonicSort(a, low, k, 1);

		bitonicSort(a, low + k, k, 0);

		bitonicMerge(a, low, cnt, dir);
	}
}

void BiggerSource::compAndSwap(long long* a, int i, int j, int dir)
{
	if (dir == (a[i] > a[j]))
		swap(i, j);
}

void BiggerSource::bitonicMerge(long long *a, int low, int cnt, int dir)
{
	if (cnt>1)
	{
		int k = cnt / 2;
		for (int i = low; i<low + k; i++)
			compAndSwap(a, i, i + k, dir);
		bitonicMerge(a, low, k, dir);
		bitonicMerge(a, low + k, k, dir);
	}
}

void BiggerSource::bitonicSort(long long* a, int low, int cnt, int dir)
{
	if (cnt>1)
	{
		int k = cnt / 2;

		bitonicSort(a, low, k, 1);

		bitonicSort(a, low + k, k, 0);

		bitonicMerge(a, low, cnt, dir);
	}
}




