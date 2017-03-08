#include "BiggerSource.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <stack>

int BiggerSource::init_num = 0;

void BiggerSource::readFile(const char* file_name)
{

    std::vector<unsigned char> buffer;
    char temp_var[128];
    char line[513];
    int index;
    size_t line_number;
    int category;

    std::ifstream file(file_name,
        std::ios::binary | std::ios::in);

    if(file.fail())
    {
        perror("Error in opening line");
        perror(file_name);
        exit(2);
    }

    line_number = 0;

    ResultDS(;);

    while(file.getline(line, 512, '\n')){
        category = 0;
        index = 0;
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
                        if(*buffer_iter == ',')
                            temp_var[index] = '\0';
                        else{
                            temp_var[index++] = *buffer_iter;
                            temp_var[index] = '\0';
                        }
                        headers.push_back(std::string(temp_var));
                        index = 0;
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
                    case 0: //scheme_prog_code
                        scheme_prog_code = (atoi(temp_var));
                        break;
                    case 1: //prepared_date
						prepared_date = std::string(temp_var);
                        break;
                    case 2: //declared_date
						declared_date = std::string(temp_var);
                        break;
                    case 3: //prog_name
						prog_name = std::string(temp_var);
                        break;
                    case 4: //prog_sem_year
						prog_sem_year = std::string(temp_var);
                        break;
                    case 5: //batch
                        batch = (atoi(temp_var));
                        break;
                    case 6: //examination
						examination = std::string(temp_var);
                        break;
                    case 7: //institution_code
                        institution_code = (atoi(temp_var));
                        break;
                    case 8: //institution_name
						institution_name = std::string(temp_var);
                        break;
                    case 9: //rollnumber
                        rollnumber = (atoll(temp_var));
                        break;
                    case 10: //name
						name = std::string(temp_var);
                        break;
                    case 11: //sid
                        sid = (atoll(temp_var));
                        break;
                    case 12: //result_scheme_id
                        result_scheme_id = (atoll(temp_var));
                        break;
					case 13:
						paper_id = atoi(temp_var);
						break;
                    case 14: //credits
						credits = std::string(temp_var);
                        break;
                    case 15: //minor
						minor = std::string(temp_var);
                        break;
                    case 16: //major
						major = std::string(temp_var);
                        break;
                    case 17: //total
						total = std::string(temp_var);
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

                this->rollnumber[line_number-1] = rollnumber;
                this->name[line_number-1] = std::string(name);
                this->paper_id[line_number-1] = paper_id;

                resultsDataStructure[line_number-1].modifyRDS(
                      scheme_prog_code, prepared_date, declared_date, prog_name, prog_sem_year,
                      batch, examination, institution_code, institution_name, rollnumber,
                      name, sid, result_scheme_id, paper_id, credits, minor, major, total
                );

            }

            line_number++;

    }

    file.close();

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

void BiggerSource::print_table(const char * file_name)
{

    FILE * p_file;
	FILE * single_col_file;
	std::string sorted_file_name(file_name);

	sorted_file_name.replace(sorted_file_name.end() - 4,
		sorted_file_name.end(), "_big_");

	sorted_file_name += std::to_string(init_num);
	sorted_file_name += ".csv";

	fopen_stream(&p_file, file_name, "w");
	fopen_stream(&single_col_file, sorted_file_name.c_str(), "w");

    std::vector<std::string>::iterator iter;
    for(iter = headers.begin();
        iter != headers.end(); ++iter){
            if(iter != headers.begin())
                printf_stream(p_file, ",");
            printf_stream(p_file,"%s",(*iter).c_str());
    }

    printf_stream(p_file,"\n");

    struct ResultsDSHolder resultsDSHolder;

    for(size_t i=0; i < rows; i++){

        resultsDataStructure[i].getValue(&resultsDSHolder);

		printf_stream(p_file, "%d,%s,%s,%s,%s,%d,%s,%d,%s,%lld,%s,%lld,%lld,%d,%s,%s,%s,%s\n",
			resultsDSHolder.scheme_prog_code, resultsDSHolder.prepared_date.c_str(),
            resultsDSHolder.declared_date.c_str(), resultsDSHolder.prog_name.c_str(),
			resultsDSHolder.prog_sem_year.c_str(), resultsDSHolder.batch,
            resultsDSHolder.examination.c_str(), resultsDSHolder.institution_code,
            resultsDSHolder.institution_name.c_str(), resultsDSHolder.rollnumber,
            resultsDSHolder.name.c_str(), resultsDSHolder.sid, resultsDSHolder.result_scheme_id,
            resultsDSHolder.paper_id, resultsDSHolder.credits.c_str(), resultsDSHolder.minor.c_str(),
			resultsDSHolder.major.c_str(), resultsDSHolder.total.c_str());

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

    fclose(p_file);
	fclose(single_col_file);

}

void BiggerSource::MemAllo()
{
    size_t colmns = 18;
    rows = ResultsDataStructure::MAX_SIZE;

    headers.reserve(colmns);

	paper_id = new int[rows];
    rollnumber = new long long[rows];
    name = new std::string[rows];

    resultsDataStructure = new ResultsDataStructure[rows];

	init_num++;

}

void BiggerSource::MemFree()
{

    headers.clear();

	delete [] paper_id;
    delete [] rollnumber;
    delete [] name;

    delete [] resultsDataStructure;

}

void BiggerSource::sort(int column)
{

	if (column == 1) {
		quicksort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 2) {
		quicksort(name, 0, rows - 1);
		sorted_col_string = name;
		sorted_col_type = string;
	}
	if (column == 3) {
		quicksort(rollnumber, 0, rows - 1);
		sorted_col_long = rollnumber;
		sorted_col_type = longe;
	}
	if (column == 4) {
		shellsort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 5) {
		shellsort(name, 0, rows - 1);
		sorted_col_string = name;
		sorted_col_type = string;
	}
	if (column == 6) {
		shellsort(rollnumber, 0, rows - 1);
		sorted_col_long = rollnumber;
		sorted_col_type = longe;
	}
	if (column == 7) {
		bubblesort(paper_id, 0, rows - 1);
		sorted_col_int = paper_id;
		sorted_col_type = inte;
	}
	if (column == 8) {
		bubblesort(name, 0, rows - 1);
		sorted_col_string = name;
		sorted_col_type = string;
	}
	if (column == 9) {
		bubblesort(rollnumber, 0, rows - 1);
		sorted_col_long = rollnumber;
		sorted_col_type = longe;
	}

}

void BiggerSource::shellsort(std::string * toSort, size_t low, size_t high)
{
	size_t i, j;
	long long k;

	size_t i_foot, j_foot, k_foot;

	i_foot = j_foot = k_foot = 0;

	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j < high; j++) {
			for (k = j - i; k >= 0; k = k - i)
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

	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j<high; j++)
			for (k = j - i; k >= 0; k = k - i)
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
	
	for (i = (high + 1) / 2; i>0; i = i / 2)
		for (j = i; j<high; j++)
			for (k = j - i; k >= 0; k = k - i)
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

    SWAP(temp_int, index_1, index_2, paper_id);
    SWAP(temp_long, index_1, index_2, rollnumber);
    SWAP(t_string, index_1, index_2, name);
    SWAP(t_resultsDataStructure, index_1, index_2, resultsDataStructure);

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

	if (str1.length() > str2.length())
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
