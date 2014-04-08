#ifndef __GasStation_h__
#define __GasStation_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std::tr1;

class Solution {
public:
	// Not a DP
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
		for (int i = 0; i < gas.size(); ++i) {
			float remGas = 0;
			bool isFound = true;
			for (int j = 0; j < gas.size(); ++j) {
				int curr = i + j;
				curr = (curr < gas.size()) ? curr : curr - gas.size(); 
				remGas += gas[curr];
				if (remGas < cost[curr]) {
					isFound = false;
					i = i + j; // i = i + j but not i = curr, coz i will be monitored for whether excceed n 
					break;
				}
				remGas -= cost[curr]; // don't forget to substract after comparison
			}
			if (isFound)
				return i;
			
		}
		return -1;
    }
};

class CGasStation: public BasicQue {
public:
	void doWork() {
		Solution s;
		vector<int> gas;
		gas.push_back(2);
		gas.push_back(4);
		vector<int> cost;
		cost.push_back(3);
		cost.push_back(4);
		cout << s.canCompleteCircuit(gas, cost);
	}
};

#endif