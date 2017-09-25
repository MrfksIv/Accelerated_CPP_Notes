// AcceleratedCPPChapter05.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Student_info.h"
#include <iostream>
#include <string>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

int main()
{
	std::string name;
	std::cout << "Please enter your name: ";
	std::cin >> name;
	std::string::size_type maxlength = 0;
	std::cout << "Hello, " + name << ". Please enter your students names below: ";
	

	Student_info tempStudent;
	std::vector<Student_info> students;
	while (read(std::cin, tempStudent)) {
		students.push_back(tempStudent);
		std::cout << "Read " << tempStudent.name << " with final: " << tempStudent.final << "and homework count of " << tempStudent.homeworks.size() << " total: " << students.size()<< std::endl;
		std::cout <<"Final Grade: " <<  grade(tempStudent) << std::endl;
		maxlength = std::max(maxlength, tempStudent.name.size());
	}
	std::cout << "You have given details for " << students.size() << " students.." << std::endl;

	//std::sort(students.begin(), students.end(), compare);
	for (std::vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
		std::cout << students[i].name << std::string(maxlength - students[i].name.size() + 2, ' ');

		try {
			double final_grade = grade(students[i]);
			std::streamsize prec = std::cout.precision();
			std::cout << std::setprecision(3) << final_grade << std::setprecision(prec);
		}
		catch (std::domain_error e) {
			std::cout << e.what();
			return -1;
		}

		std::cout << std::endl;
		
	}
	std::cout << "This is the end of the report. Press enter to quit";

	std::string end;
	std::cin >> end;
    return 0;
	std::cout << "Hello, " + name << ". Please enter your students names below: ";
}

