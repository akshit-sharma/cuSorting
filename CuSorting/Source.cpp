#include "Source.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>

int Source::init_num = 0;

void Source::readFile(const char* file_name)
{
	std::vector<unsigned char> buffer;
	char temp_var[128];
	char line[513];
	int index;
	int line_number;
	int category;

    int scheme_prog_code; std::string prog_name; long long scheme_id; std::string prog_sem_year;
    std::string prepared_date; std::string declared_date; int institution_code;
    std::string institution_name;	int s_number;	int paper_id;	std::string paper_code;
    std::string subject_name;	int credits; std::string type; std::string exam; std::string mode;
    std::string kind;	std::string minor; std::string major; std::string max_marks; std::string pass_marks;


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
					if (*buffer_iter == ',')
						temp_var[index] = '\0';
					else
					{
						temp_var[index++] = *buffer_iter;
						temp_var[index] = '\0';
					}
					headers.push_back(std::string(temp_var));
					index = 0;
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
				case 0:
					scheme_prog_code = (atoi(temp_var));
					break;
				case 1:
					prog_name = std::string(temp_var);
					break;
				case 2:
					scheme_id = (atoll(temp_var));
					break;
				case 3:
					prog_sem_year = std::string(temp_var);
					break;
				case 4:
					prepared_date = std::string(temp_var);
					break;
				case 5:
					declared_date = std::string(temp_var);
					break;
				case 6:
					institution_code = (atoi(temp_var));
					break;
				case 7:
					institution_name = std::string(temp_var);
					break;
				case 8:
					s_number = (atoi(temp_var));
					break;
				case 9:
					paper_id = (atoi((temp_var)));
					break;
				case 10:
					paper_code = std::string(temp_var);
					break;
				case 11:
					subject_name = std::string(temp_var);
					break;
				case 12:
					credits = (atoi(temp_var));
					break;
				case 13:
					type = std::string(temp_var);
					break;
				case 14:
					exam = std::string(temp_var);
					break;
				case 15:
					mode = std::string(temp_var);
					break;
				case 16:
					kind = std::string(temp_var);
					break;
				case 17:
					minor = std::string(temp_var);
					break;
				case 18:
					major = std::string(temp_var);
					break;
				case 19:
					max_marks = std::string(temp_var);
					break;
				case 20:
					pass_marks = std::string(temp_var);
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
            this->institution_name[line_number - 1] = std::string(institution_name);
            this->paper_id[line_number - 1] = paper_id;
            this->subject_name[line_number - 1] = std::string(subject_name);

            schemeDataStructure[line_number-1].modifySDS(
                    scheme_prog_code, prog_name, scheme_id, prog_sem_year,
                    prepared_date, declared_date, institution_code,
                    institution_name, s_number, paper_id, paper_code,
                    subject_name, credits, type, exam, mode,
                    kind, minor, major, max_marks, pass_marks
            );
        }

		line_number++;
	}

	file.close();
}

bool Source::readFileToBuffer(std::string filePath,
                              std::vector<unsigned char>& buffer)
{
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

void Source::print_table(const char* file_name)
{
	FILE* p_file;
	FILE* single_col_file;
	std::string sorted_file_name(file_name);
	int i_value;
	std::string s_value;

	sorted_file_name.replace(sorted_file_name.end() - 4,
	                         sorted_file_name.end(), "_sma_");

	sorted_file_name += std::to_string(init_num);
    sorted_file_name += ".csv";

	fopen_stream(&p_file, file_name, "w");
	fopen_stream(&single_col_file, sorted_file_name.c_str(), "w");

	std::vector<std::string>::iterator iter;
	for (iter = headers.begin();
	     iter != headers.end(); ++iter)
	{
		if (iter != headers.begin())
		printf_stream(p_file, ",");
		printf_stream(p_file,"%s",(*iter).c_str());
	}

	printf_stream(p_file,"\n");

    struct SchemeDSHolder schemeDSHolder;

	for (size_t i = 0; i < rows; i++)
	{

        schemeDataStructure[i].getValue(&schemeDSHolder);

		printf_stream(p_file, "%d,%s,%lld,%s,%s,%s,%d,%s,%d,%d,%s,%s,%d,%s,%s,%s,%s,%s,%s,%s,%s\n",
            schemeDSHolder.scheme_prog_code, schemeDSHolder.prog_name.c_str(), schemeDSHolder.scheme_id, schemeDSHolder.prog_sem_year.c_str(),
            schemeDSHolder.prepared_date.c_str(), schemeDSHolder.declared_date.c_str(), schemeDSHolder.institution_code, schemeDSHolder.institution_name.c_str(),
            schemeDSHolder.s_number, schemeDSHolder.paper_id, schemeDSHolder.paper_code.c_str(), schemeDSHolder.subject_name.c_str(), schemeDSHolder.credits,
            schemeDSHolder.type.c_str(), schemeDSHolder.exam.c_str(), schemeDSHolder.mode.c_str(), schemeDSHolder.kind.c_str(),
            schemeDSHolder.minor.c_str(), schemeDSHolder.major.c_str(), schemeDSHolder.max_marks.c_str(), schemeDSHolder.pass_marks.c_str())
		;

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

	fclose(p_file);
	fclose(single_col_file);
}

void Source::MemAllo()
{
	size_t colmns = 21;
	rows = SchemeDataStructure::MAX_SIZE;

	headers.reserve(colmns);

	paper_id = new int[rows];
	institution_name = new std::string[rows];
	subject_name = new std::string[rows];

    schemeDataStructure = new SchemeDataStructure[rows];

	init_num++;

}

void Source::MemFree()
{
	headers.clear();

	delete [] (institution_name);
	delete [] (paper_id);
	delete [] (subject_name);

    delete [] (schemeDataStructure);

}

void Source::sort(int column)
{
	if (column == 1)
	{
		quicksort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 2)
	{
		quicksort(subject_name, 0, rows - 1);
		sorted_col_string = subject_name;
		sorted_col_type = string;
	}
	if (column == 3)
	{
		quicksort(institution_name, 0, rows - 1);
		sorted_col_string = institution_name;
		sorted_col_type = string;
	}
	if (column == 4)
	{
		shellsort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 5)
	{
		shellsort(subject_name, 0, rows - 1);
		sorted_col_string = subject_name;
		sorted_col_type = string;
	}
	if (column == 6)
	{
		shellsort(institution_name, 0, rows - 1);
		sorted_col_string = institution_name;
		sorted_col_type = string;
	}
	if (column == 7)
	{
		bubblesort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 8)
	{
		bubblesort(subject_name, 0, rows - 1);
		sorted_col_string = subject_name;
		sorted_col_type = string;
	}
	if (column == 9)
	{
		bubblesort(institution_name, 0, rows - 1);
		sorted_col_string = institution_name;
		sorted_col_type = string;
	}
}


void Source::shellsort(std::string* toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;


	for (i = (high + 1) / 2; i > 0; i = i / 2)
		for (j = i; j < high; j++)
			for (k = j - i; k >= 0; k = k - i)
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

	for (i = (high + 1) / 2; i > 0; i = i / 2)
		for (j = i; j < high; j++)
			for (k = j - i; k >= 0; k = k - i)
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

    SWAP(t_int, index_1, index_2, paper_id);
    SWAP(t_string, index_1, index_2, subject_name);
    SWAP(t_string, index_1, index_2, institution_name);
    SWAP(t_schemeDataStructure, index_1, index_2, schemeDataStructure);

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

	if (str1.length() > str2.length())
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

