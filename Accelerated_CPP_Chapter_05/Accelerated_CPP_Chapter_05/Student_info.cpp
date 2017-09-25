
#include "stdafx.h"
#include <string>
#include <vector>
#include <istream>
#include "median.h"

struct Student_info {
	std::string name;
	double final, midterm;
	std::vector<double> homeworks;
};

bool compare(const Student_info& x, const Student_info& y) {
	return x.name < y.name;
}

double grade(double midterm, double final, double homework) {
	return 0.2 * midterm + 0.4 * final + 0.4 * homework;
}

double grade(const Student_info& student) {
	double med = median(student.homeworks);
	return grade(student.midterm, student.final, med);
}

std::istream& read_hw(std::istream& in, std::vector<double>& homeworks) {
	if (in) {
		homeworks.clear();

		double hwGrade;
		while (in >> hwGrade) {
			homeworks.push_back(hwGrade);
		}
		in.clear();
	}
	return in;
}

std::istream& read(std::istream& in, Student_info& s) {

	in >> s.name >> s.midterm >> s.final;
	read_hw(in, s.homeworks);
	return in;
}

