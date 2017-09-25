//
//  median.cpp
//  accelerated_cpp_chapter4_02
//
//  Created by Κωνσταντινος Μορφακης on 24/09/2017.
//  Copyright © 2017 Κωνσταντινος Μορφακης. All rights reserved.
//

#include "median.h"
#include <vector>
#include <algorithm>
#include <vector>
#include <stdexcept>

using std::vector; using std::sort; using std::domain_error;

double median(vector<double> vec) {
    
    vector<double>::size_type vec_sz = vec.size();
    if (vec_sz == 0) {
        throw domain_error("Student hasn't given in any homeworks.");
    }
    sort(vec.begin(), vec.end());
    vector<double>::size_type mid = vec_sz / 2;
    
    return vec_sz % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2: vec[mid];
}
