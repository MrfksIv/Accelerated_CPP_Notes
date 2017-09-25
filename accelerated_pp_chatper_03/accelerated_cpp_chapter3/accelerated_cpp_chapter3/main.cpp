//
//  main.cpp
//  accelerated_cpp_chapter3
//
//  Created by Κωνσταντινος Μορφακης on 17/08/16.
//  Copyright © 2016 Κωνσταντινος Μορφακης. All rights reserved.
//

#include <algorithm>
#include <vector>
#include <iostream>
#include <iomanip>  //defines the manipulator setprecision (lets us choose how many significant digits we want for the output)
#include <ios>      //defines streamsize (is what the input/output lib uses to represent sizes)
#include <string>

using std::cout;    using std::cin;
using std::string;  using std::setprecision;
using std::endl;    using std::streamsize;

using std::vector;  using std::sort;


void gradesV0();


int main(int argc, const char * argv[]) {
    // insert code here...
    
//    gradesV0();
    string name;
    int count = 0;
    double midterm, final, sum, grade;
    
    std::vector<double> hwgrades;
    
    cout << "Please enter your first name: ";
    cin >> name;
    cout << "Hello, " + name +"!" << endl;
    cout << "Please enter your mditerm followed by your final grade: ";
    
    cin >> midterm >> final;
    
    sum= 0;
    cout << "Enter all of your h/w grades followed by EOF: ";
    while (cin >> grade) {
        sum += grade;
        hwgrades.push_back(grade);
        ++count;
    }
    
    // Different implementations use different types to represent sizes so
    // we cannot write the appropriate type of size directly and remail implementation independent.
    // Therefore, it is good programming practice to use the size_type property that represents
    // the number of elements in a vector with the appropriate type that guarantees to hold the biggest possible vector.
    
    // Because writing everytime "vector<double>::size_type" to define such a variable is too long, we 'save'
    // it in a shorter version using typedef (or a synonym):
    typedef vector<double>::size_type vec_size; // now we can use 'vec_size'
    vec_size size = hwgrades.size();                 // to initialise variables of type vector<double>::size_type
    
    
    if (size == 0) {
        cout<<"You have to at least complete 1 homework to pass." <<endl;
        return -1;
    } else {
        std::sort(hwgrades.begin(), hwgrades.end());
        vec_size mid = size / 2;
        double median;
        median = size % 2 == 0 ? (hwgrades[mid] + hwgrades[mid - 1])/2 : hwgrades[mid];
        
        cout << "The median of your " << size << " homeworks is: " << median << endl;
    }
    
    streamsize prec = cout.precision();
    cout << "Your final grade is " <<setprecision(3)
    << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
    << setprecision((int)prec) << endl;
    
    return 0;
}

void gredesV0() {
    
    string name;
    int count = 0;
    double midterm, final, sum, grade;
    
    cout << "Please enter your first name: ";
    cin >> name;
    cout << "Hello, " + name +"!" << endl;
    cout << "Please enter your mditerm followed by your final grade: ";
    
    cin >> midterm >> final;
    
    sum= 0;
    cout << "Enter all of your h/w grades followed by EOF";
    while (cin >> grade) {
        sum += grade;
        ++count;
    }
    
    streamsize prec = cout.precision();
    cout << "Your final grade is " <<setprecision(3)
    << 0.2 * midterm + 0.4 * final + 0.4 * sum / count
    << setprecision((int)prec) << endl;
    
}
