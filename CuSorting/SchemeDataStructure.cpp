#include "SchemeDataStructure.h"

decltype(SchemeDataStructure::paper_id) SchemeDataStructure::getPaperId() {
	return paper_id;
}

void SchemeDataStructure::modifySDS(
		SchemeDS(COMMA)
)
{

    this->scheme_prog_code = scheme_prog_code;
    this->prog_name = std::string(prog_name);
    this->scheme_id = scheme_id;
    this->prog_sem_year = std::string(prog_sem_year);
    this->prepared_date = std::string(prepared_date);
    this->declared_date = std::string(declared_date);
    this->institution_code = institution_code;
    this->institution_name = std::string(institution_name);
    this->s_number = s_number;
    this->paper_id = paper_id;
    this->paper_code = std::string(paper_code);
    this->subject_name = std::string(subject_name);
    this->credits = credits;
    this->type = std::string(type);
    this->exam = std::string(exam);
    this->mode = std::string(mode);
    this->kind = std::string(kind);
    this->minor = std::string(minor);
    this->major = std::string(major);
    this->max_marks = std::string(max_marks);
    this->pass_marks = std::string(pass_marks);

	this->orig_scheme_prog_code = this->scheme_prog_code;
	this->orig_prog_name = this->prog_name;
	this->orig_scheme_id = this->scheme_id;
	this->orig_prog_sem_year = this->prog_sem_year;
	this->orig_prepared_date = this->prepared_date;
	this->orig_declared_date = this->declared_date;
	this->orig_institution_code = this->institution_code;
	this->orig_institution_name = this->institution_name;
	this->orig_s_number = this->s_number;
	this->orig_paper_id = this->paper_id;
	this->orig_paper_code = this->paper_code;
	this->orig_subject_name = this->subject_name;
	this->orig_credits = this->credits;
	this->orig_type = this->type;
	this->orig_exam = this->exam;
	this->orig_mode = this->mode;
	this->orig_kind = this->kind;
	this->orig_minor = this->minor;
	this->orig_major = this->major;
	this->orig_max_marks = this->max_marks;
	this->orig_pass_marks = this->pass_marks;

}

void SchemeDataStructure::getValue(struct SchemeDSHolder * schemeDSHolder)
{

    schemeDSHolder->scheme_prog_code = this->scheme_prog_code;
    schemeDSHolder->prog_name = this->prog_name;
    schemeDSHolder->scheme_id = this->scheme_id;
    schemeDSHolder->prog_sem_year = this->prog_sem_year;
    schemeDSHolder->prepared_date = this->prepared_date;
    schemeDSHolder->declared_date = this->declared_date;
    schemeDSHolder->institution_code = this->institution_code;
    schemeDSHolder->institution_name = this->institution_name;
    schemeDSHolder->s_number = this->s_number;
    schemeDSHolder->paper_id = this->paper_id;
    schemeDSHolder->paper_code = this->paper_code;
    schemeDSHolder->subject_name = this->subject_name;
    schemeDSHolder->credits = this->credits;
    schemeDSHolder->type = this->type;
    schemeDSHolder->exam = this->exam;
    schemeDSHolder->mode = this->mode;
    schemeDSHolder->kind = this->kind;
    schemeDSHolder->minor = this->minor;
    schemeDSHolder->major = this->major;
    schemeDSHolder->max_marks = this->max_marks;
    schemeDSHolder->pass_marks = this->pass_marks;

}

SchemeDataStructure SchemeDataStructure::getOriginalValue()
{

	SchemeDataStructure returnSchemeDataStructure;

	returnSchemeDataStructure.scheme_prog_code = this->orig_scheme_prog_code;
	returnSchemeDataStructure.prog_name = this->orig_prog_name;
	returnSchemeDataStructure.scheme_id = this->orig_scheme_id;
	returnSchemeDataStructure.prog_sem_year = this->orig_prog_sem_year;
	returnSchemeDataStructure.prepared_date = this->orig_prepared_date;
	returnSchemeDataStructure.declared_date = this->orig_declared_date;
	returnSchemeDataStructure.institution_code = this->orig_institution_code;
	returnSchemeDataStructure.institution_name = this->orig_institution_name;
	returnSchemeDataStructure.s_number = this->orig_s_number;
	returnSchemeDataStructure.paper_id = this->orig_paper_id;
	returnSchemeDataStructure.paper_code = this->orig_paper_code;
	returnSchemeDataStructure.subject_name = this->orig_subject_name;
	returnSchemeDataStructure.credits = this->orig_credits;
	returnSchemeDataStructure.type = this->orig_type;
	returnSchemeDataStructure.exam = this->orig_exam;
	returnSchemeDataStructure.mode = this->orig_mode;
	returnSchemeDataStructure.kind = this->orig_kind;
	returnSchemeDataStructure.minor = this->orig_minor;
	returnSchemeDataStructure.major = this->orig_major;
	returnSchemeDataStructure.max_marks = this->orig_max_marks;
	returnSchemeDataStructure.pass_marks = this->orig_pass_marks;

	return returnSchemeDataStructure;

}


void SchemeDataStructure::setValue(SchemeDataStructure * schemeDataStructure)
{

	this->scheme_prog_code = schemeDataStructure->scheme_prog_code;
	this->prog_name = schemeDataStructure->prog_name;
	this->scheme_id = schemeDataStructure->scheme_id;
	this->prog_sem_year = schemeDataStructure->prog_sem_year;
	this->prepared_date = schemeDataStructure->prepared_date;
	this->declared_date = schemeDataStructure->declared_date;
	this->institution_code = schemeDataStructure->institution_code;
	this->institution_name = schemeDataStructure->institution_name;
	this->s_number = schemeDataStructure->s_number;
	this->paper_id = schemeDataStructure->paper_id;
	this->paper_code = schemeDataStructure->paper_code;
	this->subject_name = schemeDataStructure->subject_name;
	this->credits = schemeDataStructure->credits;
	this->type = schemeDataStructure->type;
	this->exam = schemeDataStructure->exam;
	this->mode = schemeDataStructure->mode;
	this->kind = schemeDataStructure->kind;
	this->minor = schemeDataStructure->minor;
	this->major = schemeDataStructure->major;
	this->max_marks = schemeDataStructure->max_marks;
	this->pass_marks = schemeDataStructure->pass_marks;

}
