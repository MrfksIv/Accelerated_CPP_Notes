#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "Student_info.h"

using std::vector;

double median(vector<double> vec) {
	vector<double>::size_type vec_size = vec.size();
	if (vec_size == 0) {
		throw std::domain_error("Median cannot be computed for vectors of length 0");
	}
	std::sort(vec.begin(), vec.end());
	vector<double>::size_type mid = vec_size/2;

	return vec_size % 2 == 0 ? (vec[mid-1] + vec[mid])/2: vec[mid];
}