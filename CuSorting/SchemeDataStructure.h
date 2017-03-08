#pragma once
#include <string>


#define SWAP(type, var_1, var_2, data_member)        \
	type = data_member[var_1];	                     \
	data_member[var_1] = data_member[var_2];	     \
	data_member[var_2] = type;

struct SchemeDSHolder{
	int scheme_prog_code;
	std::string prog_name;
	long long scheme_id;
	std::string prog_sem_year;
	std::string prepared_date;
	std::string declared_date;
	int institution_code;
	std::string institution_name;		//
	int s_number;
	int paper_id;						//
	std::string paper_code;
	std::string subject_name;			//
	int credits;
	std::string type;
	std::string exam;
	std::string mode;
	std::string kind;
	std::string minor;
	std::string major;
	std::string max_marks;
	std::string pass_marks;
};

class SchemeDataStructure
{
	int scheme_prog_code;
	std::string prog_name;
	long long scheme_id;
	std::string prog_sem_year;
	std::string prepared_date;
	std::string declared_date;
	int institution_code;
	std::string institution_name;		//
	int s_number;
	int paper_id;						//
	std::string paper_code;
	std::string subject_name;			//
	int credits;
	std::string type;
	std::string exam;
	std::string mode;
	std::string kind;
	std::string minor;
	std::string major;
	std::string max_marks;
	std::string pass_marks;

public:
    static const size_t MAX_SIZE = 247659;

	void modifySDS(
			int scheme_prog_code, std::string prog_name, long long scheme_id, std::string prog_sem_year,
			std::string prepared_date, std::string declared_date, int institution_code,
			std::string institution_name,	int s_number,	int paper_id,	std::string paper_code,
			std::string subject_name,	int credits, std::string type, std::string exam, std::string mode,
			std::string kind,	std::string minor, std::string major, std::string max_marks, std::string pass_marks
	);
	void getValue(struct SchemeDSHolder * schemeDSHolder);

};
