// Chapter_07.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <algorithm>

using std::string; using std::map;
using std::istream; using std::vector;

bool space(char);
bool not_space(char);
std::vector<std::string> split(const std::string&); 
std::map<std::string, std::vector<int> > xref(std::istream&, std::vector<std::string> find_words(const std::string&));

int main()
{
	std::string s;
	std::string ss;
	std::map<std::string, int> counters;

	map<string, vector<int> > ret = xref(std::cin, split);

	for (map<string, vector<int> >::const_iterator it = ret.begin(); it != ret.end(); ++it) {
		std::cout << it->first << " occurs on line(s): ";

		vector<int>::const_iterator line_it = it->second.begin();
		std::cout << *line_it;
		++line_it;

		while (line_it != it->second.end()) {
			std::cout << ", " << *line_it;
			++line_it;
		}
		std::cout << std::endl;
	}

	while (std::cin >> s) {
		// we increment the entry for word s by 1. If the word is encountered for the
		// first time, the map automatically creates a new element with that key which is
		// value initialised: For integers, this means setting it to 0.
		++counters[s];
	}

	for (std::map<std::string, int>::const_iterator it = counters.begin();
			it != counters.end(); ++it) {
		std::cout << it->first << "\t" << it->second << std::endl;
		std::cout << (*it).first << "\t" << (*it).second << std::endl;
	}
	std::cout << "Please enter something to continue..." << std::endl;
	std::cin >> ss;
    return 0;
}

bool space(char c) {
	return std::isspace(c);
}

bool not_space(char c) {
	return !space(c);
}

std::vector<std::string> split(const std::string& str) {
	typedef std::string::const_iterator iter;
	std::vector<std::string> ret;

	iter i = str.begin();
	while (i != str.end()) {
		
		
		// find_if takes two iterators as a range and a third predicate.
		// It tests the predicate on every element in the range iteratively, until
		// it returns true.
		// Here, it ignores the leading blanks by returning the first occurence
		// of a non-space character.
		i = std::find_if(i, str.end(), not_space);

		// find end of next word
		iter j = std::find_if(i, str.end(), space);

		if (i != str.end()) {
			ret.push_back(std::string(i, j));
		}
		i = j;
	}
	return ret;
}

std::map<std::string, std::vector<int> > xref(std::istream& in,
	std::vector<std::string> find_words(const std::string&) = split) 
{
	string line;
	int line_number = 0;
	map<string, vector<int> > ret;

	// The getline() is defined in the string library. It takes two arguments:
	// The first is the istream from which to read and the second is a reference to 
	// a string in which to store what is read.
	while (std::getline(in, line)) {
		++line_number;

		// break the input line into words
		vector<string> words = find_words(line);

		// remember that each word occurs on the current line
		for (vector<string>::const_iterator it = words.begin(); it != words.end(); ++it) {
			// value is initialisation of class types (vector in this case) means that when push_back() is
			// called for a first-seen word, an empty vector is created first and then the value is pushed back.
			ret[*it].push_back(line_number);
		}
	}
	return ret;
}

