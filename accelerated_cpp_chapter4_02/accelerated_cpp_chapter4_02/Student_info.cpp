//
//  Student_info.cpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#include "Student_info.hpp"
#include "grade.hpp"
#include <vector>

using std::vector;
using std::istream;

bool compare(const Student_info& x, const Student_info& y) {
    return x.name < y.name;
}

bool fgrade(const Student_info& s) {
    return grade(s) > 60;
}



istream& read_hw(istream& in, vector<double>& hw) {
    if (in) {
        hw.clear();
        
        double hw_grade;
        while(in >> hw_grade) {
            hw.push_back(hw_grade);
        }
        in.clear();
    }
    return in;
}


istream& read(istream& in, Student_info& s){
    in >> s.name >> s.midterm >> s.final;
    read_hw(in, s.homework);
    return in;
}
