#include "student_index.h"

StudentIndex::StudentIndex(unsigned long long fn, unsigned long long get)
{
	fac_num_ = fn;
	get_ptr_ = get;
}

bool StudentIndex::operator>(StudentIndex & other)
{
	return fac_num_ > other.fac_num_;
}

bool StudentIndex::operator<(StudentIndex & other)
{
	return fac_num_ < other.fac_num_;
}

istream & operator>>(istream & is, StudentIndex & index)
{
	is >> index.fac_num_;
	is >> index.get_ptr_;
	return is;
}

ostream & operator<<(ostream & os, StudentIndex & index)
{
	os << index.fac_num_;
	os << index.get_ptr_;
	return os;
}

