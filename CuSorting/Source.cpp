#include "Source.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>

int Source::init_num = 0;

double Source::preSorting() {

	clock_t start;
	size_t index;
	start = startTimer();

	switch (column_decide%3)
	{

	case 0:
		sorted_col_string = institution_name;
		sorted_col_type = string;
		break;
	case 1:
		sorted_col_int = paper_id;
		sorted_col_type = inte;

		if (column_decide % 3 == 1)
			for (index = rows; index < max2Rows; index++)
				this->paper_id[index] = INT_MAX;
		break;
	case 2:
		sorted_col_string = subject_name;
		sorted_col_type = string;
		break;

	default:
		break;
	}

	return getTimeElapsed(start, endTimer());
}

double Source::sort()
{
	clock_t start;
	start = startTimer();

	switch (column_decide)
	{
	case 1:
		quicksort(paper_id, 0, rows - 1);
		break;
	case 2:
		quicksort(subject_name, 0, rows - 1);
		break;
	case 3:
		quicksort(institution_name, 0, rows - 1);
		break;
	case 4:
		bitonicSort(paper_id, 0, max2Rows, 1);
		break;
	case 5:
		shellsort(subject_name, 0, rows - 1);
		break;
	case 6:
		shellsort(institution_name, 0, rows - 1);
		break;
	case 7:
		bubblesort(paper_id, 0, rows - 1);
		break;
	case 8:
		bubblesort(subject_name, 0, rows - 1);
		break;
	case 9:
		bubblesort(institution_name, 0, rows - 1);
		break;
	default:
		break;
	}
	return getTimeElapsed(start, endTimer());
}

double Source::postSorting()
{
	clock_t start;
	start = startTimer();

	return getTimeElapsed(start, endTimer());
}

size_t Source::getFileLines(const char* file_name) 
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

double Source::readFile(const char* file_name)
{
	clock_t start;
	start = startTimer();

	std::vector<unsigned char> buffer;
	char temp_var[128];
	char line[513];
	int index;
	int line_number;
	int category;

	int paper_id;
	std::string subject_name;
	std::string institution_name;

	bool overpassed_inst = NULL;
	bool overpassed_subj = NULL;

    for(index=0;index<128;index++)
        temp_var[index] = '\0';

	std::ifstream file(file_name,
	                   std::ios::binary | std::ios::in);
	if (file.fail())
	{
		perror("Error in opening line");
		perror(file_name);
		exit(2);
	}

	line_number = 0;

	while (file.getline(line, 512, '\n'))
	{
		category = 0;
		index = 0;
		
		if (line_number >= rows)
			break;

		for (char* buffer_iter = line;
		     *buffer_iter != '\0'; ++buffer_iter)
		{
			if (*buffer_iter == '\n')
			{
				line_number++;
				index = 0;
				continue;
			}

			if (line_number == 0)
			{
				if (*buffer_iter == ',' || *(buffer_iter + 1) == '\0')
				{
					continue;
				}
			}

			if (*buffer_iter == ',' || (*(buffer_iter + 1) == '\0' && line_number != 0))
			{
				if (*buffer_iter == ',')
					temp_var[index] = '\0';
				else
				{
					temp_var[index++] = *buffer_iter;
					temp_var[index] = '\0';
				}
                if(line_number>=rows)
                    break;
				switch (category)
				{
				case 7:
					institution_name = std::string(temp_var);
					break;
				case 9:
					paper_id = (atoi((temp_var)));
					break;
				case 11:
					subject_name = std::string(temp_var);
					break;
				default:
					break;
				}
				index = 0;
				++category;
				category %= 21;
			}
			else
			{
				temp_var[index++] = *buffer_iter;
			}
		}

        if(line_number != 0) {
			
        	if(column_decide%3==0)
				this->institution_name[line_number - 1] = std::string(institution_name);

			if(column_decide%3==1)
				this->paper_id[line_number - 1] = paper_id;
            
			if(column_decide%3==2)
        		this->subject_name[line_number - 1] = std::string(subject_name);
			
        }

		line_number++;
	}

	file.close();

		
	return getTimeElapsed(start, endTimer());
}

bool Source::readFileToBuffer(std::string filePath,
                              std::vector<unsigned char>& buffer)
{
	clock_t start;
	start = startTimer();

	std::ifstream file(filePath,
	                   std::ios::binary | std::ios::in);
	if (file.fail())
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

double Source::print_table(const char* file_name)
{
	clock_t start;
	start = startTimer();

	FILE* single_col_file;
	std::string sorted_file_name(file_name);
	int i_value;
	std::string s_value;

	sorted_file_name.replace(sorted_file_name.end() - 4,
	                         sorted_file_name.end(), "_sma_");

	sorted_file_name += std::to_string(init_num);
    sorted_file_name += ".csv";

	fopen_stream(&single_col_file, sorted_file_name.c_str(), "w");
	
	for (size_t i = 0; i < rows; i++)
	{
		
		switch (sorted_col_type)
		{
		case inte:
			i_value = sorted_col_int[i];
			printf_stream(single_col_file, "%d\n", i_value);
			break;
		case string:
			s_value = sorted_col_string[i];
			printf_stream(single_col_file, "%s\n", s_value.c_str());
			break;
		}
	}

	fclose(single_col_file);

	return getTimeElapsed(start, endTimer());
}

void Source::selectColumn(int column)
{
	this->column_decide = column;
	this->rows = 0;
}

void Source::setRows(size_t size)
{
	this->rows = size;
}

size_t Source::getRowsCount()
{
	return this->rows;
}

double Source::MemAllo(const char* file_name)
{
	clock_t start;
	start = startTimer();

	size_t colmns = 21;

	if(rows==0)
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

	paper_id = new int[max2Rows];
	institution_name = new std::string[rows];
	subject_name = new std::string[rows];
	
	length_institution_name = 0;
	length_subject_name = 0;

	maxLength_inti = 0;
	maxLength_subj = 0;

	init_num++;

	return getTimeElapsed(start, endTimer());

}

double Source::MemFree()
{
	clock_t start;
	start = startTimer();


	delete [] (institution_name);
	delete [] (paper_id);
	delete [] (subject_name);

	return getTimeElapsed(start, endTimer());
}

void Source::shellsort(std::string* toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;

	high++;
	for (i = (high + 1) / 2; i > 0; i = i / 2)
		for (j = i; j < high; j++)
			for (k = j - i; k >= 0 &&
				compare_isMore(toSort[k],toSort[k+i]); k = k - i)
			{
				if (compare_isLess(toSort[k], toSort[k + i]))
					break;
				else
					swap(k, k + i);
			}
}

void Source::shellsort(int* toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;

	high++;
	for (i = (high + 1) / 2; i > 0; i = i / 2)
		for (j = i; j < high; j++)
			for (k = j - i; k >= 0 &&
				toSort[k] > toSort[k + i]; k = k - i)
			{
				if (toSort[k] < toSort[k + i])
					break;
				else
					swap(k, k + i);
			}
}

void Source::bubblesort(std::string * toSort, size_t low, size_t high)
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

void Source::bubblesort(int * toSort, size_t low, size_t high)
{
	size_t i, j;
	bool anySwap = false;

	for (i = high; i > low; i--){
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


void Source::quicksort(int* toSort, size_t low, size_t high)
{
	std::stack<size_t> mini_stack;

	mini_stack.push(low);
	mini_stack.push(high);

	while (mini_stack.size() > 0)
	{
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


void Source::quicksort(std::string* toSort, size_t low, size_t high)
{
	std::stack<size_t> mini_stack;

	mini_stack.push(low);
	mini_stack.push(high);

	while (mini_stack.size() > 0)
	{
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

size_t Source::partition(int* toSort, size_t low, size_t high)
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

size_t Source::partition(std::string* toSort, size_t low, size_t high)
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


void Source::swap(const size_t index_1, const size_t index_2)
{

	int t_int;
    std::string t_string;
    SchemeDataStructure t_schemeDataStructure;

	switch (column_decide%3)
	{
	case 0:
		SWAP(t_string, index_1, index_2, institution_name);
		break;
	case 1:
		SWAP(t_int, index_1, index_2, paper_id);
		break;
	case 2:
		SWAP(t_string, index_1, index_2, subject_name);
		break;
	}
	
}

bool Source::compare_isLess(std::string str1, std::string str2)
{
	size_t i;
	size_t min_i;
	i = 0;

	min_i = std::min(str1.length(), str2.length());

	while (i < min_i)
	{
		if (str1[i] < str2[i])
		{
			return true;
		}
		else if (str1[i] > str2[i])
		{
			return false;
		}
		++i;
	}

	if (str1.length() < str2.length())
		return true;

	return false;
}

bool Source::compare_isMore(std::string str1, std::string str2)
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

bool Source::checkComputation()
{
	int paper_id_old, paper_id_new;
	std::string subject_name_old, subject_name_new;
	std::string institution_name_old, institution_name_new;

	paper_id_old = INT_MIN;
	subject_name_old = "";
	institution_name_old = "";

	for (size_t i = 0; i < rows; i++) {

		switch (column_decide % 3)
		{
		case 0:
			institution_name_new = institution_name[i];
			if (compare_isMore(institution_name_old, institution_name_new))
				return false;
			institution_name_old = institution_name_new;
			break;
		case 1:
			paper_id_new = paper_id[i];
			if (paper_id_old > paper_id_new)
				return false;
			paper_id_old = paper_id_new;
			break;
		case 2:
			subject_name_new = subject_name[i];
			if (compare_isMore(subject_name_old, subject_name_new))
				return false;
			subject_name_old = subject_name_new;
			break;
		default:
			break;
		}

	}

	return true;

}

std::clock_t Source::startTimer() 
{
	return std::clock();
}

std::clock_t Source::endTimer()
{
	return std::clock();
}

double Source::getTimeElapsed(std::clock_t start, std::clock_t end)
{
	return (end - start) / static_cast<double>(CLOCKS_PER_SEC);
}

void Source::compAndSwap(int* a, int i, int j, int dir)
{
	int t_int;
	if (dir == (a[i] > a[j]))
		swap(i, j);
}

void Source::bitonicMerge(int* a, int low, int cnt, int dir)
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

void Source::bitonicSort(int* a, int low, int cnt, int dir)
{
	if (cnt>1)
	{
		int k = cnt / 2;

		bitonicSort(a, low, k, 1);

		bitonicSort(a, low + k, k, 0);

		bitonicMerge(a, low, cnt, dir);
	}
}

