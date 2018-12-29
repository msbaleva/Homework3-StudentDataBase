#ifndef STUDENTDATABASE_STUDENTDATABASE_STUDENT_INDEX_H_
#define STUDENTDATABASE_STUDENTDATABASE_STUDENT_INDEX_H_
#include <iostream>
#include <string>
using namespace std;
struct StudentIndex {
	unsigned long long fac_num_;
	unsigned long long get_ptr_;
	StudentIndex(unsigned long long = 0, unsigned long long = 0);
	bool operator>(StudentIndex&);
	bool operator<(StudentIndex&);
	friend istream& operator>>(istream&, StudentIndex&);
	friend ostream& operator<<(ostream&, StudentIndex&);
	
};

#endif