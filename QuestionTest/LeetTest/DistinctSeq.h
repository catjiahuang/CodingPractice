#ifndef __DistinctSeq_h__
#define __DistinctSeq_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    int numDistinct(string S, string T) {
		vector <vector <int>> dp(T.length() + 1);
		for (int i = 0; i < dp.size(); ++i) {
			dp[i].resize(S.length() + 1);
			dp[i][0] = 0;
		}
		for (int j = 0; j < dp[0].size(); ++j)
			dp[0][j] = 1;
		for (int i = 1; i <= T.length(); ++i) {
			for (int j = 1; j <= S.length(); ++j) {
				dp[i][j] = dp[i][j-1];
				if (T.at(i-1) == S.at(j-1))
					dp[i][j] += dp[i-1][j-1];
			}
		}
		return dp[T.length()][S.length()];
    }
};

class CDistinctSeq: public BasicQue {
public:
	void doWork() {
		
	}
};

#endif