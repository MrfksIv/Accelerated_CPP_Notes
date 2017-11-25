// Accelerated_CPP_Chapter_08.cpp : Defines the entry point for the console application.
//
/*
 * WRITING GENERIC FUNCTIONS
 *
 * We have already used functions whose parameter and return types are unknown until 
 * they are called. An example is the function 'find()' which takes 2 iterators as arguments.
 * These can be string or vector iterators or any other 'appropriate type'.
 *
 * Functions such as 'find()' are called generic because they can work with multiple (appropriate)
 * types. 
 */


#include "stdafx.h"
#include <stdio.h>
#include <string>
#include <algorithm>
#include <vector>

using std::vector;			using std::sort;
using std::domain_error;	using std::swap;

// This was our initial median function written in $4.1.1/53 used to calculate the median of a vector<double>.
// Note that the function will not work with vector<int> - We would need to rewrite the function to achieve that.
double median_old(vector<double> vec) {
	typedef vector<double>::size_type vec_sz;
	vec_sz size = vec.size();
	
	if (size == 0)
		throw domain_error("Cannot calculate median of an empty vector.");

	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

// We can use templates to write the median function in a way to support vectors of multiple types

// The template header tells the implementation that we are defining a template function that will take
// a TYPE PARAMETER. Type parameters are like function parameters - i.e. they define names that can be used
// within the scope of the function. 
// The difference is that type parameters refer to TYPES NOT TO VARIABLES. When we call this median() function,
// 'T' will be binded to a type determined during compilation.
template <class T>  
T median(vector<T> vec) {
	// 'typename' is added here to tell the implementation that vector<T>::size_type is the name of a type even 
	// even though the implementation doesn't yet know what type 'T' is. 
	typedef typename vector<T>::size_type vec_sz;
	vec_sz size = vec.size();

	if (size == 0)
		throw domain_error("Cannot calculate median of an empty vector.");

	sort(vec.begin(), vec.end());
	vec_sz mid = size / 2;

	// calling median with vector<double> does the arithmetic on double values.
	// The same happes with vector<int>. However, calling median with vector<string>
	// will not work because division '/' is not defined for string types. Thus, string
	// is not an appropriate type for this generic function.
	return size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid];
}

// We can use templates to establish how algorithms such as find work behind the scenes. Notice that 
// the types passed need to accept the operators '++', '!=' and '*'.
template<class In, class Out>
In our_find(In begin, In end, Out elem) {
	while (begin != end && *begin != elem)
		++begin;
	return begin;
}

// However, we could have also written our_find in the following way. This adds to the supported operators
// list '=='. Th
template<class In, class Out>
In our_find(In begin, In end, Out elem) {
	if (begin == end || *begin == elem)
		return begin;
	begin++;
	return our_find(begin, end, elem);
}

/*
 * ITERATOR TYPES
 * --------------
 * SEQUENTIAL READ-ONLY ACCESS - INPUT ITERATOR
 * From the two exaples above, we can conclude that an iterator that offers sequential, read-only access to elements
 * of a sequence should support:
 * 1) ++ (both prefix and postfix)
 * 2) ==
 * 3) != 
 * 4) * and -> 
 * 
 * If an operator, supports all the above operations, we call it an INPUT ITERATOR. There exist five iterator types in
 * in total.
 *
 * SEQUENTIAL WRITE-ONLY ACCESS - OUTPUT ITERATOR
 * Often we need to be able to use iterators to write elements of a sequence. Consider the our_copy() function below.
 * As the name in suggests, begin and end are input iterators. We use them only for reading elements as in our_find().
 * The Out iterator should support:
 * 1) ++ (both prefix and postfix)
 * 2) * (unary pointer NOT multiplication)
 * 3) Implicit requirement to NOT execute ++it more than once between assignments, and not assign a value to *it more
 *    than once between increments.
 */
template <class In, class Out>
Out our_copy(In begin, In end, Out dest) {
	while (begin != end)
		*dest++ = *begin++;
	return dest;
}

/*
 * SEQUENTIAL READ-WRITE ACCESS - FORWARD ITERATOR
 * We should be able to read and write elements of a sequence, but only sequentially - we intend to advance iterators
 * forward but never backward. An example is the function replace() rewritten below.
 * Notice that the type For iterator should support all of the requirements of the Input AND Output operators.
 * Overall it should support:
 * 1) *it (for both reading and writing) and the equivalent it->member of (*it).member
 * 2) ++it and it++ but not (--it or it--)
 * 3) it == j and it != j (where j is the same type as it)
 */
template<class For, class X>
void replace(For beg, For end, const X& x, const X& y) {
	while (beg != end) {
		if (*beg == x)
			*beg = y;
		++beg;
	}
}

/* REVERSIBE ACCESS - BIDIRECTIONAL ITERATOR
 * Some functions such as reverse() need to get to a container's elements in reverse order.
 * A bidirectional Iterator supports all the operations of the Forward iterator and in addition, supports 
 * the -- (both prefix and postfix).
 */
template<class Bi>
void reverse(Bi begin, Bi end) {
	while (begin != end) {
		--end;
		if (begin != end)
			swap(*begin++, *end)
	}
}

/*RANDOM ACCESS*/ 



int main()
{
    return 0;
}

