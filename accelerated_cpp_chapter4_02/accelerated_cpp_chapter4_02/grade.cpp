//
//  grade.cpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#include "grade.hpp"
#include "median.h"

#include <vector>
#include "Student_info.hpp"
#include "median.h"


using std::vector;

double grade(double midterm, double final, const vector<double>& hw) {
    double med = median(hw);
    return 0.2 * midterm + 0.4 * final + 0.4 * med;
}


double grade(const Student_info& s) {
    return grade(s.midterm, s.final, s.homework);
}
