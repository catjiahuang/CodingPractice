#ifndef __LongConsecSeq_h__
#define __LongConsecSeq_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std::tr1;

class Solution {
public:
    int longestConsecutive(vector<int> &num) {
        unordered_set <int> numSet;
		for (int i = 0; i < num.size(); ++i)
			numSet.insert(num[i]);
		int maxCnt = 0, tmpCnt = 0;
		for (int i = 0; i < num.size(); ++i) {
			if (numSet.find(num[i]) != numSet.end()) {
				int val = num[i];
				tmpCnt = 1;
				while (numSet.find(val + 1) != numSet.end()) {
					numSet.erase(val + 1);
					tmpCnt++;
					val++;
				}
				val = num[i];
				while (numSet.find(val - 1) != numSet.end()) {
					numSet.erase(val - 1);
					tmpCnt++;
					val--;
				}
				if (tmpCnt > maxCnt)
					maxCnt = tmpCnt;
			}
		}
		return maxCnt;
    }
};

class CLongConsecSeq: public BasicQue {
public:
	void doWork() {
		int num[] = {100, 4, 200, 1, 3, 2};
		vector <int> num1(num, num + 6);
		Solution sln;
		cout << sln.longestConsecutive(num1);
	}
};

#endif