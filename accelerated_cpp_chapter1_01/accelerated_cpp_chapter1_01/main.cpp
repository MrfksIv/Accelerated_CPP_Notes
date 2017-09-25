//
//  main.cpp
//  accelerated_cpp_chapter1_01
//
//  Created by Κωνσταντινος Μορφακης on 07/08/16.
//  Copyright © 2016 Κωνσταντινος Μορφακης. All rights reserved.
//

#include <iostream>
#include <string>


int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, please enter your name: ";
    std::string name;
    std::cin >> name;
    
    //the message that we intend to write
    const std::string greeting = "Hello, " + name + "!";
    
    
    //build the second and fourth lines
    const std::string spaces(greeting.size(), ' ');
    const std::string second = "* "+ spaces + " *";
    
    //build the first and fifth lines of the output
    const std::string first(greeting.size()+4, '*');
    
    std::cout << std::endl;
    std::cout << first << std::endl;
    std::cout << second << std::endl;
    std::cout << "* " << greeting << " *" << std::endl;
    std::cout << second << std::endl;
    std::cout << first << std::endl;
    
    
    return 0;
}
