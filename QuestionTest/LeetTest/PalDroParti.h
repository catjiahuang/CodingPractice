#ifndef __PalDroParti_h__
#define __PalDroParti_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	bool isParti(string s) {
		int bg = 0, ed = s.length() - 1;
		while (bg < ed) {
			if (s[bg] != s[ed])
				return false;
			else {
				bg++;
				ed--;
			}
		}
		return true;
	}

	void partHelper(vector<vector<string>> &res, vector<string> &part, string &s, int id) {
		if (id == s.length()) {
			res.push_back(part);
			return;
		}
		for (int i = (int)s.length()-1; i >= id; --i) {
			string subs = s.substr(id, i-id+1);
			if (isParti(subs)) {
				vector<string> newPart = part;
				newPart.push_back(subs);
				partHelper(res, newPart, s, i + 1);
			}
		}
	}

    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
		if (s.empty())
			return res;
		vector<string> part;
		partHelper(res, part, s, 0);
		return res;
	}

	// find min number of cut
	int minCut(string s) {
		int len = s.length();

		int* dp = new int[len+1];
		int** parti = new int*[len];
		for (int i = 0; i < len; ++i)
			parti[i] = new int[len];

		for (int i = 0; i <= len; ++i)
			dp[i] = len - i;
		for (int i = 0; i < len; ++i)
			for (int j = 0; j < len; ++j)
				parti[i][j] = false;

		for (int i = len - 1; i >= 0; --i) {
			for (int j = i; j < len; ++j) {
				if (s[i] == s[j] && (j-i < 2 || parti[i+1][j-1])) {
					parti[i][j] = true;
					dp[i] = min(dp[i], dp[j+1] + 1);
				}
			}
		}
		return dp[0]-1;
    }
};

class CPalDroParti: public BasicQue {
public:
	void doWork() {
		Solution sln;
		string s = "abbba";//"abcaba";//"aab";//"";//"abcaba";//"aabb";
		vector<vector<string>> res = sln.partition(s);

		for (unsigned i = 0; i < res.size(); ++i) {
			for (unsigned j = 0; j < res[i].size(); ++j)
				cout << res[i][j] << " ";
			cout << endl;
		}
		cout << sln.minCut(s);
	}
};

#endif