// AcceleratedCPPChapter06.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cctype>

using std::vector; using std::string; using std::copy;
using std::back_inserter; using std::isspace;

vector<string> joinStrVecs(vector<string>& a, const vector<string> b) {
	for (vector<string>::const_iterator iter = b.begin(); iter != b.end(); ++iter) {
		a.push_back((*iter));
	}
	return a;
}

// Because the isspace() function is by design overloaded (to be able to work with other 
// languages) this causes problem when we use it as a predicate in the find_if() call below. 
// To avoid this problem, we create our own versions of it, so that it is clear to the compiler
// what version we need.
bool space(char c) {
	return isspace(c);
}
bool not_space(char c) {
	return !isspace(c);
}

// palindromes are words that can be read both from left to right and right to left.
// 
bool is_palindrome(const string& s) {
	return std::equal(s.begin(), s.end(), s.rbegin());
}


void printStringVec(const vector<string>& s, char ch) {
	for (vector<string>::const_iterator iter = s.begin(); iter != s.end(); ++iter) {
		std::cout << (*iter);
		if (iter != s.end() - 1) {
			std::cout << ch;
		}
	}
	std::cout << std::endl;
}

// the main idea behind this function is to look in a string for white space, 
// define words as the letters between spaces, and append those words to a vector.
vector<string> split(const string& str) {
	
	// <string> does support some of the operations of <vector> such as iterators:
	typedef string::const_iterator iter;
	vector<string> ret;

	iter i = str.begin();
	while (i != str.end()) {

		// the first two arguments of find_if() are iterators and the third is a predicate
		// which tests its argument and return true/false. It calls the predicate on each 
		// element in the sequence, stopping when it finds an element that returns true.
		// Otherwise it returns its second argument.
		// As a result, the find_if() call below, finds the first non-space character
		i = std::find_if(i, str.end(), not_space);
		
		// The next find_if() does the opposite: Stops at the first instance of a white-space 
		// character.
		iter j = std::find_if(i, str.end(), space);

		if (i != str.end()) {
			ret.push_back(string(i, j));
		}
		i = j;
	}
}

int main()
{
	vector<string> firstPart = { "This", "is", "a" "string", "vector" };
	vector<string> secondPart = { "followed", "by", "another", "vector." };

	vector<string> thirdPart = { "LA", "LA", "LA", "LA" };
	vector<string> fourthPart = { "LO", "LO", "LO", "LO" };
	
	// There exist two ways to concatenate two vectors:
	joinStrVecs(firstPart, secondPart);

	printStringVec(firstPart, '_');

	// Alternatively, we could use the .insert() method as shown below. The arguments are \
	([start-appending-at], [first-element-to-append], [last-element-to-append])

	thirdPart.insert(thirdPart.end(), secondPart.begin(), secondPart.end());
	printStringVec(thirdPart, '-');
	
	// however, there exists an even more general solution:
	copy(fourthPart.begin(), fourthPart.end(), back_inserter(secondPart));
	// The last solution is an example of a GENERIC ALGORITHM that is not part of any particular kind
	// of container that adapts its behaviour depending on its arguments' types.
	// (Usually, the standard library's generic algorithms take iterators among theira arguments
	printStringVec(secondPart, ' ');

    return 0;
}

