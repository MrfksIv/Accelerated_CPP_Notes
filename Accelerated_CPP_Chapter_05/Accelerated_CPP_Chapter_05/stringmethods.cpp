#include "stdafx.h"
#include <vector>
#include <string>
#include <cctype> // includes useful functions for processing individual characters

using std::vector; using std::string;

vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;
	
	// we will use i as the index that finds the start of each word advancing 
	string_size i = 0;

	// the first while-loop makes sure that we stop as soon as we process the whole string
	while (i != s.size()) {
		
		// increment i until we find a non-whitespace character
		while (i != s.size() && std::isspace(s[i])) {
			++i;
		}

		// since we are out of the above loop, we have found a non-whitespace character. We
		// save this in j.
		string_size j = i;

		// increment j until we find a whitespace character. When we do, j signifies the end
		// of the wor(l)d.
		while (j != s.size() && !std::isspace(s[i])) {
			++j;
		}

		// now, i signifies the beginning of the word, and j the end. If they are equal, it 
		// means that j == s.size() thus we are at the end of the string.
		if (i != j) {
			ret.push_back(s.substr(i, j - 1));
			i = j;
		}
	}
	return ret;
}