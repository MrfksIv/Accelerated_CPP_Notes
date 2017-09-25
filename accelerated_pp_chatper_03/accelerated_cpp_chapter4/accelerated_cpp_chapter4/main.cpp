//
//  main.cpp
//  accelerated_cpp_chapter4
//
//  Created by Κωνσταντινος Μορφακης on 20/08/16.
//  Copyright © 2016 Κωνσταντινος Μορφακης. All rights reserved.
//

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <ios>

using std::cout;            using std::cin;
using std::setprecision;    using std::streamsize;
using std::endl;            using std::vector;
using std::domain_error;    using std::istream;

double median(vector<double> vec) {
    typedef vector<double>::size_type vec_sz;
    vec_sz size = vec.size();
    
    if (size == 0)
        throw domain_error("median of an empty vector");
    
    sort(vec.begin(), vec.end());
    vec_sz mid = size / 2;
    
    return mid % 2 == 0 ? (vec[mid-1] +vec[mid])/2 : vec[mid];
}

double grade(double midterm, double final, double hw){
    return 0.2*midterm + 0.4*final + 0.2*hw;
}

double grade(double midterm, double final, const vector<double> & hw){
    if(hw.size() ==0)
        throw domain_error("Student has given in no homeworks!");
    return grade(midterm,final, median(hw));
}

istream& read_hw(istream& in, vector<double>& hw) {
    
    return in;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    streamsize prec = cout.precision();
    double final, midterm;
    vector<double> homeworks;
    
    cout << "Please enter your midterm followed by the final exam grade:";
    cin >> midterm >> final;
    
    cout << "Enter all of your homework grades followed by end-of-file:";
    
    double x;
    while(cin >> x){
        homeworks.push_back(x);
    }
    
    
    cout << "Your final grade is " << setprecision(3)
    << grade(midterm, final, homeworks)
    << setprecision(prec) << endl;
    return 0;
}



