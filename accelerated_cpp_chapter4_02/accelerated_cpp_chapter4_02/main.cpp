//
//  main.cpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

#include "Student_info.hpp"
#include "grade.hpp"

using std::string;          using std::vector;
using std::istream;         using std::sort;
using std::cin;             using std::domain_error;
using std::cout;            using std::endl;
using std::max;             using std::streamsize;
using std::setprecision;
// suppose we want to keep student names and grades together, and then
// display them in alphabetical order. To do this, each student name
// must be held with its corresponding grades. This can be done using
// a struct:

int main(int argc, const char * argv[]) {
    cout << "Please enter the Students record below:" << endl;
    vector<Student_info> students;
    Student_info record;
    string::size_type maxlen = 0;
    
    while(read(cin, record)) {
        maxlen = max(maxlen, record.name.size());
        students.push_back(record);
    }
    
    sort(students.begin(), students.end(), compare);
    
    for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
        cout << students[i].name << string(maxlen - students[i].name.size() + 1, ' ');
        
        try {
            double final_grade = grade(students[i]);
            streamsize prec = cout.precision();
            cout << setprecision(3) << final_grade << setprecision((int)prec);
        } catch(domain_error e) {
            cout << e.what();
        }
        
        cout << endl;
    }
    return 0;
}
