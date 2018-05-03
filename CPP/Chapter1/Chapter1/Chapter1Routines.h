#ifndef WEISS_YHK_CHAPTER1ROUTINES_H
#define WEISS_YHK_CHAPTER1ROUTINES_H
/**
* Exercise 1, Chapter 1.
* Solves k-selection problem.
* I use random selection and pivot, similar to quick sort.
*/
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include "Rectangle.h"
#include <functional>
#include <random>

/* Selects k-th element, using the following routine.
Choose an element randomly, compare it to all the elements in the array and put smaller elements from the left
and larger elements to the right. If the chosen element is k-th element we are done, otherwise repeat the routine
with the left sub array if we have chosen element larger than k-th or to the right if have chosen element smaller than k.
Update the borders accordingly. */
template <class Comparable>
Comparable select(int k, std::vector<Comparable> v) {
	// operating range from which to chose
	int lowIndex = 0;
	int highIndex = v.size() - 1;

	int chosenIndex = -1;
	int numberOfIterations = 0;

	while (chosenIndex != k) {
		int range = highIndex - lowIndex + 1;
		chosenIndex = lowIndex + rand() % range;
		std::swap(v[lowIndex], v[chosenIndex]);
		chosenIndex = lowIndex;

		for (int checkedIndex = lowIndex + 1; checkedIndex <= highIndex; checkedIndex++) {
			if (v[checkedIndex] < v[chosenIndex] || (v[checkedIndex] == v[chosenIndex] && rand() % 2 == 0)) {
				std::swap(v[checkedIndex], v[chosenIndex + 1]);
				std::swap(v[chosenIndex], v[chosenIndex + 1]);
				chosenIndex++;
			}
		}

		if (chosenIndex > k) highIndex = chosenIndex - 1;
		if (chosenIndex < k) lowIndex = chosenIndex + 1;
		numberOfIterations++;
	}

	std::cout << "Number of iterations " << numberOfIterations << "\n";
	return v[chosenIndex];
}

/*
* Generic maximal elemement with a vector using function object as a comparator.
*
*/
template <typename Object, typename Comparator>
const Object & findMax(const std::vector<Object> & arr, Comparator isLessThan) {
	int maxIndex = 0;

	for (int i = 0; i < arr.size(); ++i) {
		bool result = isLessThan(arr[maxIndex], arr[i]);
		if (result) {
			maxIndex = i;
		}
	}

	return arr[maxIndex];
}

template <typename Object>
const Object & findMax(const std::vector<Object> & arr) {
	return findMax(arr, std::less<Object>{});
}


#endif