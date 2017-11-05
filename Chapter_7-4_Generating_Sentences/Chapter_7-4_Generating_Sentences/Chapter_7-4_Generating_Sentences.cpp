// Chapter_7-4_Generating_Sentences.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using std::string; using std::map; using std::vector;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

Grammar read_grammar(std::istream&);
vector<string> split(const string&);
bool space(char);
int randn(int);

int main()
{
	// generate the sentence
	vector<string> sentence = gen_sentence(read_grammar(std::cin));

	// write the first word if any
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		std::cout << *it;
		++it;
	}

	//write the rest of the words separated by spaces
	while (it != sentence.end()) {
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
    return 0;
}


bool space(char c) {
	return std::isspace(c);
}

bool bracketed(const string& s) {
	return s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>';
}

vector<string> split(const string& s) {

	vector<string> words;

	for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
		it = std::find_if(it, s.end(), !space);

		string::const_iterator j = std::find_if(it, s.end(), space);
		if (it != s.end()) {
			words.push_back(string(it, j));
		}
		it = j;
	}
	return words;
}

Grammar read_grammar(std::istream& in) {
	Grammar ret;
	string line;

	while (std::getline(in, line)) {
		vector<string> entry = split(line);

		if (!entry.empty())
			ret[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
	}
	return ret; 
}

vector<string> gen_sentence(const Grammar& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

void gen_aux(const Grammar& g, const string& word, vector<string>& ret) {
	
	// if the word is not bracketed, it is a 'regular' word so just add it to the vector
	if (!bracketed(word)) {
		ret.push_back(word);
	}
	else {
		// otherwise, locate the rule that corresponds to the word
		Grammar::const_iterator it = g.find(word);
		if (it == g.end()) {
			throw std::logic_error("empty rule");
		}

		// fetch the set of possible rules
		const Rule_collection& c = it->second;

		// from which we select one at arandom
		const Rule& r = c[nrand(c.size())];

		// recursively expand the selected rule
		for (Rule::const_iterator i = r.begin(); i != r.end(); ++i) {
			gen_aux(g, *i, ret);
		}
	}
}

int nrand(int n) {
	if (n <= 0 || n > RAND_MAX) {
		throw std::domain_error("Argument to nrand is out of range");
	}
	const int bucket_size = RAND_MAX / n;
	int r;

	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}