#pragma once
#ifndef Student_info_h
#define Student_info_h

#include <string>
#include <vector>
#include <istream>

struct Student_info {
	std::string name;
	double final, midterm;
	std::vector<double> homeworks;
};

bool compare(const Student_info& x, const Student_info& y);

double grade(const Student_info&);
double grade(double, double, double);

std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>);

#endif
