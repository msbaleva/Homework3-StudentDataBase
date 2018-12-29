#ifndef STUDENTDATABASE_STUDENTDATABASE_OPERATIONS_H_
#define STUDENTDATABASE_STUDENTDATABASE_OPERATIONS_H_
#include <fstream>
#include "student.h"
#include "student_index.h"
#include <vector>



void sequentialSearch() {
	fstream file;
	file.open("StudentsGrades.db", ios::in);
	if (!file) { cerr << "File couldn't be opened!\n"; }
	Student st;
	unsigned long long fn;
	do { cin >> fn; } while (fn<0 || fn>pow(2, 50));
	bool found = false;
	file.seekg(0, ios::beg);
	while (file >> st) {

		if (st.getFacNum() == fn) { cout << st; found = true; break; }

	}
	if (!found) { cout << "Record not found!\n"; }
	file.close();

}


void quickSort(vector<StudentIndex> &indexVector, int left, int right) {
	int i, j, middle;
	StudentIndex pivotIndex,tempIndex;
		i = left;
		j = right;
		middle = left + (right - left) / 2;
		pivotIndex = indexVector[middle];

		while (i<right || j>left) {
			while (indexVector[i] < pivotIndex)
				i++;
			while (indexVector[j] > pivotIndex)
				j--;

			if (i <= j) {
				tempIndex = indexVector[i];
				indexVector[i] = indexVector[j];
				indexVector[j] = tempIndex;
				i++;
				j--;
			}
			else {
				if (i < right)
					quickSort(indexVector, i, right);
				if (j > left)
					quickSort(indexVector, left, j);
				return;
			}
		}
	}



void buildIndex() {


	vector<StudentIndex> indexVector;
	fstream file;
	file.open("StudentsGrades.db", ios::in);
	if (!file) { cerr << "File couldn't be opened!\n"; }
	Student st;
	file.seekg(0, ios::beg);
	unsigned long long getPtr = file.tellg();
	while (file >> st) {

		indexVector.push_back(StudentIndex(st.getFacNum(), getPtr));
		getPtr = file.tellg();
	}

	file.close();
	quickSort(indexVector,0,indexVector.size()-1);
	file.open("FacultyNumber.ids", ios::binary|ios::out|ios::trunc);
	if (!file) { cerr << "File couldn't be opened!\n"; }
	for (int j = 0; j < indexVector.size(); j++) {
		file.write((char*)&indexVector[j], sizeof(StudentIndex));
	}
	
	file.close();
	cout << "Index is built!\n";
}


void search() {
	fstream binFile;
	binFile.open("FacultyNumber.ids", ios::in|ios::binary);
	if (!binFile) { cerr << "File FacultyNumber.ids couldn't be opened!\n"; }
	StudentIndex index;
	unsigned long long fn;
	do { cin >> fn; } while (fn<0 || fn>pow(2, 50));
	binFile.seekg(0, ios::end);
	unsigned long long n = binFile.tellg() / sizeof(StudentIndex);
	StudentIndex leftIndex, rightIndex, middleIndex;
	int middle, left = 0, right = n - 1;
	binFile.seekg(left * sizeof(StudentIndex));
	binFile.read((char*)&leftIndex, sizeof(StudentIndex));
	binFile.seekg(right * sizeof(StudentIndex));
	binFile.read((char*)&rightIndex, sizeof(StudentIndex));
	unsigned long long foundPosition = -1;
	if(fn < leftIndex.fac_num_ || fn > rightIndex.fac_num_) { cout << "Record not found!\n"; return; }
	if (fn == leftIndex.fac_num_) { foundPosition = leftIndex.get_ptr_; }
	else {
		while (right - left > 1) {
			middle = (left + right) / 2;
			binFile.seekg(middle * sizeof(StudentIndex));
			binFile.read((char*)& middleIndex, sizeof(StudentIndex));
			if (fn <= middleIndex.fac_num_) { right = middle; }
			else { left = middle; }
		}
		binFile.seekg(right * sizeof(StudentIndex));
		binFile.read((char*)& rightIndex, sizeof(StudentIndex));
		if (fn == rightIndex.fac_num_) { foundPosition = rightIndex.get_ptr_; }
		else { cout << "Record not found!\n"; return; }
	}
	binFile.close();
	ifstream file;
	file.open("StudentsGrades.db", ios::in);
	if (!file) { cerr << "File couldn't be opened!\n"; }
	file.seekg(foundPosition, ios::beg);
	Student st;
	file >> st;
	cout << st;
	file.close();
}
void operationParser() {
	string input;
	cin >> input;
	while (input != "exit") {

		if (input == "sequentialSearch") {
			sequentialSearch();
		}
		else if (input == "search") {
			search();
		}
		else if (input == "buildIndex") {
			buildIndex();
		}
		else { cout << "Invalid operation!\n"; }
		cin >> input;
	}
}

void generateDataBase() {
	
		fstream nameFile;
		fstream numFile;
		nameFile.open("names.db", ios::in | ios::out);
		if (!nameFile) { cerr << "File couldn't be opened!\n"; }
		numFile.open("facultyNums.db", ios::in | ios::out);
		if (!numFile) { cerr << "File couldn't be opened!\n"; }
		fstream file;
		file.open("StudentsGrades.db", ios::app);
		if (!file) { cerr << "File couldn't be opened!\n"; }
		unsigned long long fn;
		string name;
		string family;
		unsigned short int grade;
		for (int i = 0; i < 1000000; i++) {
			fn = i;
			numFile >> fn;
			nameFile >> name;
			nameFile >> family;
			
			grade = rand() % 5 + 2;
			Student st(fn, name, family, grade);
			file << st;

		}

		nameFile.close();
		numFile.close();
		file.close();
	
}


#endif