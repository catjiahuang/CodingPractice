#ifndef __SingleNum_h__
#define __SingleNum_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int singleNumber(int A[], int n) {
		int res = A[0];
		for (int i = 1; i < n; i++) {
			res ^= A[i];
		}
		return res;
    }
	int singleNumber2(int A[], int n) {
		int ones = 0, twos = 0, xthrees = 0;
		for (int i = 0; i < n; ++i) {
			twos |= ones & A[i]; // twos will record the number as soon as it appears the 2nd time
			ones ^= A[i];
			xthrees = ~(ones & twos); // find numbers that appear 3 times
			ones &= xthrees; // eliminate numbers that appear 3 times
			twos &= xthrees;
		}
		return ones;
    }
};

class BasicQueExp: public BasicQue {
public:
	void doWork() {
		
	}
};

#endif