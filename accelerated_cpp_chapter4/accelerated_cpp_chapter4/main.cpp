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
    
    double median = mid % 2 == 0 ? (vec[mid-1] +vec[mid])/2 : vec[mid];
    cout << "Your h/w median is: " << median << endl;
    
    return median;
}


double grade(double midterm, double final, double hw){
    return 0.2 * midterm + 0.4 * final + 0.4 * hw;
}

// First note that we can overload the same function name if the two
// functions are defined with different parameters
//
// Also, notice that we vector<double> is passed by reference (&) instead
// of being passed by value. This means that the variable is not copied.
// Because the parameter is a const, we are promising that we are not
// going to change the value of the referenced variable

double grade(double midterm, double final, const vector<double> & hw){
    if(hw.size() ==0)
        throw domain_error("Student has given in no homeworks!");
    
    // in the overloaded call below, median also gets passed the vector
    // but this time the the vector is passed by value. This makes sense
    // since we don't want to change the original order of the vector
    // when calculating the median.
    return grade(midterm,final, median(hw));
}

// Here we define a referenced parameter but which is not of type const as
// before. This is an indication that we are planning to modify the object
// that is the function's argument.
istream& read_hw(istream& in, vector<double>& hw) {
    
    // If in is in failure state or run out of input, we don't do anything
    // else than simply return it unchanged.
    if (in) {
        // since we no longer define hw (the caller defines it) we don't
        // know what data might be there already - there might be grades
        // of a previous student. To solve this problem, we clear it.ß
        hw.clear(); // <- .clear() for vectors empties the vector
        
        double x;
        while (in >> x) {
            hw.push_back(x);
        }
        // we exit the while loop above either when we reach EOF or when we
        // encounter something that isn't a grade. In either case, the input
        // stream will be in failure state. To reset the error state inside
        // 'in' we call .clear() method - now input can continue despite the
        // failure.
        in.clear(); // <- .clear() for istreams resets the error indications
    }
    return in;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    streamsize prec = cout.precision();
    double final, midterm;
    vector<double> homeworks;
    
    cout << "Please enter your midterm followed by the final exam grade: ";
    cin >> midterm >> final;
    
    cout << "Enter all of your homework grades followed by end-of-file: ";
    
    read_hw(cin, homeworks);
    
    try {
        double final_grade = grade(midterm, final, homeworks);
        cout << "Your final grade is: " << setprecision(3) << final_grade << setprecision(prec) << endl;
    } catch (domain_error) {
        cout << endl << "You must enter your grades - Please try again." << endl;
        return 1;
    }
    return 0;
    
}



