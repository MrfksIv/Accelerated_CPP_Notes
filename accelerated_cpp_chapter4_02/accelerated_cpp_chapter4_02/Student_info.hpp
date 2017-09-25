//
//  Student_info.hpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#ifndef Student_info_hpp
#define Student_info_hpp

#include <iostream>
#include <string>
#include <vector>

struct Student_info {
    std::string name;
    double midterm, final;
    std::vector<double> homework;
};

bool compare(const Student_info&, const Student_info&);
bool fgrade(const Student_info&);

std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif /* Student_info_hpp */
