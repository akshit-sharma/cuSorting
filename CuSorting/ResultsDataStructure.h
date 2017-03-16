//
// Created by akshit on 7/3/17.
//

#ifndef PROJECT_RESULTSDATASTRUCTURE_H
#define PROJECT_RESULTSDATASTRUCTURE_H

#include <string>

#define SWAP(type, var_1, var_2, data_member)        \
	type = data_member[var_1];	                     \
	data_member[var_1] = data_member[var_2];	     \
	data_member[var_2] = type;

#define COMMA ,

#define ResultDS(delimiter)                                 \
    int scheme_prog_code delimiter                                   \
    std::string prepared_date delimiter                              \
    std::string declared_date delimiter                              \
    std::string prog_name delimiter                                  \
    std::string prog_sem_year delimiter                              \
    int batch delimiter                                              \
    std::string examination delimiter                                \
    int institution_code delimiter                                   \
    std::string institution_name delimiter                           \
    long long rollnumber delimiter           /* for sorting */       \
    std::string name delimiter               /* for sorting */       \
    long long sid delimiter                                          \
    long long result_scheme_id delimiter                             \
    int paper_id delimiter                   /* for sorting */       \
    std::string credits delimiter                                    \
    std::string minor delimiter                                      \
    std::string major delimiter                                      \
    std::string total

struct ResultsDSHolder{

    ResultDS(;);
    
};


class ResultsDataStructure {

    ResultDS(;);

public:
    static const size_t MAX_SIZE = 3264123;
	void modifyRDS(
		ResultDS(COMMA)	
	);
    void getValue(struct ResultsDSHolder * resultsDSHolder);

};


#endif //PROJECT_RESULTSDATASTRUCTURE_H
