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
			// stdd:string::substr only works on indices, NOT iterators. Fortunately, string
			// can be initialised in the way below by taking two iterators and returning  the 
			//characters in the range [i, j).
			ret.push_back(string(i, j));
		}
		i = j;
	}
}

bool notUrlChar(char c) {
	// local variables that are declared as static are preserved across invocations of the function.
	// This means the variable will be constructed and initialised only on the first invocation of 
	// the function. Subsequent invocations will use the object that first constructed.
	static const string url_ch = "~;/?:@=&$-_.+!*`(),";

	// isalnum is defined in the <cctype> header and tests whether its argument is alphanumeric.
	// find() looks for a specific value given as its 3rd argument. If the argument is present, it
	// returns an iterator denoting the first occurence. If the value is not present, it returns its
	// second argument.
	//
	// Because the return value is negated, the function will return false if c is alphanumeric or, one
	// of url_ch. Otherwise, it returns true.
	return !(std::isalnum(c) || std::find(url_ch.begin(), url_ch.end(), c) != url_ch.end());
}

// url_end will thus return an iterator at the first occurence of a non-url character, if one exists. 
// Otherwise, it will return its second argument (iter e).
string::const_iterator url_end(string::const_iterator b, string::const_iterator e) {
	return std::find_if(b, e, notUrlChar);
}

string::const_iterator url_begin(string::const_iterator b, string::const_iterator e) {
	static const string sep = "://";
	typedef string::const_iterator iter;

	iter i = b;

	// search takes two pairs of iterators: The first pair denotes the sequence in which we are looking,
	// and the second one denotes the string we are looking for. 
	// As with the other functions, if search fails, the second iterator is returned. This means that
	// after the call to search, i either denotes (one past) the end of the input string (e), or it a denotes
	// a ':' followed by '//'.
	while ((i = std::search(i, e, sep.begin(), sep.end())) != e) {
			
		// After finding the separator, we should isolate the protol if any. Before we do that, we check that
		// the separator is neither at the beginning, nor the end of the string.
		if (i != e && i + sep.size() != e) {

			// beg marks the beginning of the protocol-name
			iter beg = i;
			// The following while loop moves beg backwards through the input until it has either reached the
			//beginning of the string or a non-alphabetic character. 
			//Notice that if a container supports indexing, so do its iterators: beg[-1] is equivalent to *(beg - 1)
			while (beg != b && std::isalpha(beg[-1])) {
				--beg;
			}

			if (beg != i && !notUrlChar(i[sep.size()])) {
				return beg;
			}
		}
		i += sep.size();
	}
	return e;
}

vector<string> findURLs(const string & s) {
	vector<string> ret;
	typedef string::const_iterator iter;
	iter b = s.begin(), e = s.end();

	// look through the entire input string
	while (b != e) {
		// look for one or more letters followed by ://
		b = url_begin(b, e);
		
		// if we found it 
		if (b != e) {
			// get the rest of the URL
			iter after = url_end(b, e);
			
			// add the newly found URL to our result vector
			ret.push_back(string(b, after));
			
			// advance b and check for more urls
			b = after;
		}
	}
	return ret;
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

