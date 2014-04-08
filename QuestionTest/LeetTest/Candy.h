#ifndef __Candy_h__
#define __Candy_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int candy(vector<int> &ratings) {
        vector <int> res;
		res.resize(ratings.size(), 1);
		for (int i = 1; i < ratings.size(); ++i) {
			if (ratings[i] > ratings[i-1]) {
				res[i] = res[i-1] + 1;
			}
		}
		for (int i = (int)ratings.size() - 2; i >= 0; i--) {
			if (ratings[i] > ratings[i+1] && res[i] <= res[i+1]) {
				res[i] = res[i+1] + 1;
			}
		}
		int num = 0;
		for (int i = 0; i < res.size(); ++i) {
			num += res[i];
		}
		return num;
    }
};

class CCandy: public BasicQue {
public:
	void doWork() {
		
	}
};

#endif