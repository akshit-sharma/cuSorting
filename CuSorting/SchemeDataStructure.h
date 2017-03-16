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

public:
    static const size_t MAX_SIZE = 262023;

	void modifySDS(
		SchemeDS(COMMA)
	);

	void getValue(struct SchemeDSHolder * schemeDSHolder);

};

#endif //PROJECT_SCHEMEDATASTRUCTURE_H
