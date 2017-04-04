#pragma once


#ifndef PROJECT_SCHEMEDATASTRUCTURE_H
#define PROJECT_SCHEMEDATASTRUCTURE_H

#include <string>


#define SWAP(type, var_1, var_2, data_member)        \
	type = data_member[var_1];	                     \
	data_member[var_1] = data_member[var_2];	     \
	data_member[var_2] = type;

#define COMMA ,

#define SchemeDS(delimiter)									\
	int scheme_prog_code delimiter									\
	std::string prog_name delimiter									\
	long long scheme_id delimiter									\
	std::string prog_sem_year delimiter								\
	std::string prepared_date delimiter								\
	std::string declared_date delimiter								\
	int institution_code delimiter									\
	std::string institution_name delimiter		/* for sorting */	\
	int s_number delimiter											\
	int paper_id delimiter						/* for sorting */	\
	std::string paper_code delimiter								\
	std::string subject_name delimiter			/* for sorting */	\
	int credits delimiter											\
	std::string type delimiter										\
	std::string exam delimiter										\
	std::string mode delimiter										\
	std::string kind delimiter										\
	std::string minor delimiter										\
	std::string major delimiter										\
	std::string max_marks delimiter									\
	std::string pass_marks


struct SchemeDSHolder{
	
	SchemeDS(;);

};

class SchemeDataStructure
{

	SchemeDS(;);

	bool originalValue;

	int orig_scheme_prog_code;									
	std::string orig_prog_name;
	long long orig_scheme_id;
	std::string orig_prog_sem_year;
	std::string orig_prepared_date;
	std::string orig_declared_date;
	int orig_institution_code;
	std::string orig_institution_name;		/* for sorting */
	int orig_s_number;
	int orig_paper_id;						/* for sorting */
	std::string orig_paper_code;
	std::string orig_subject_name;			/* for sorting */
	int orig_credits;
	std::string orig_type;
	std::string orig_exam;
	std::string orig_mode;
	std::string orig_kind;
	std::string orig_minor;
	std::string orig_major;
	std::string orig_max_marks;
	std::string orig_pass_marks;

public:
    static const size_t MAX_SIZE = 262023;

	void modifySDS(
		SchemeDS(COMMA)
	);

	decltype(paper_id) getPaperId();

	void setValue(SchemeDataStructure * schemeDataStructure);
	SchemeDataStructure getOriginalValue();
	void getValue(struct SchemeDSHolder * schemeDSHolder);

};

#endif //PROJECT_SCHEMEDATASTRUCTURE_H
