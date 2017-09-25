//
//  grade.hpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#ifndef grade_hpp
#define grade_hpp

#include <vector>
#include "Student_info.hpp"

double grade(double, double, const std::vector<double>&);

double grade(const Student_info&);

#endif /* grade_hpp */
