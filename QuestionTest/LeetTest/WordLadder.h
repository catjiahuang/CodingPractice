#ifndef __WordLadder_h__
#define __WordLadder_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <string>

using namespace std::tr1;

class Solution {
	//bool hasTranStr(string s, unordered_set<string> &dict) {
	//	for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); ++it) {
	//		int diff = 0;
	//		for (int i = 0; i < s.length(); ++i) {
	//			if (s[i] != (*it)[i])
	//				diff++;
	//			if (diff >= 2)
	//				break;
	//		}
	//		if (diff == 1)
	//			return true;
	//	}
	//	return false;
	//}
public:
    int ladderLength(string start, string end, unordered_set<string> &dict) {
		queue <string> strQue;
		queue <int> lenQue;
		strQue.push(start);
		lenQue.push(1);
		dict.erase(start);

		while(strQue.empty() == false) {
			string str = strQue.front();
			int len = lenQue.front();
			strQue.pop();
			lenQue.pop();
			for (int i = 0; i < str.length(); ++i) {
				for (char c = 'a'; c <= 'z'; ++c) {
					char tc = str[i];
					str[i] = c;
					if (str == end) {
						return len + 1;
					}
					if (dict.find(str) != dict.end()) {
						strQue.push(str);
						lenQue.push(len+1);
						dict.erase(str);	
					}
					str[i] = tc; // change word back;
				}
			}
		}
		return 0;
	}

	// question 2: return all found paths
	void retAllPaths(string start, string last, unordered_map<string,vector<string>> &paths, vector<string> &currRes, vector<vector<string>> &res) {
		if (last == start) {
			vector<string> tRes = currRes;
			tRes.push_back(last);
			reverse(tRes.begin(), tRes.end());
			res.push_back(tRes);
		}
		else {
			for (int i = 0; i < paths[last].size(); ++i) {
				vector<string> tRes = currRes;
				tRes.push_back(last);
				retAllPaths(start, paths[last][i], paths, tRes, res);
			}
		}
	}
	
	vector<vector<string>> findLadders(string start, string end, unordered_set<string> &dict) {
		unordered_set <string> currLev, nextLev;
		unordered_map <string, vector<string>> paths; // map from found current word to all predecessor words
		currLev.insert(start);
		vector<vector<string>> res;
		
		bool isFound = false;
		while (isFound == false) {
			// remove visited words of current level
			for (unordered_set<string>::iterator it = currLev.begin(); it != currLev.end(); ++it) {
				dict.erase(*it);
			}
			// check valid variations
			for (unordered_set <string>::iterator it = currLev.begin(); it != currLev.end(); ++it) {
				string str = *it;
				for (int i = 0; i < str.length(); ++i) {
					for (char c = 'a'; c <= 'z'; ++c) {
						string tStr = str;
						tStr[i] = c;
						if (tStr == end) {
							isFound = true;
							paths[tStr].push_back(str); // record previous node
							break;
						}
						if (dict.find(tStr) != dict.end()) {
							nextLev.insert(tStr);
							paths[tStr].push_back(str); // record previous node
						}
					}
				}
			}
			// if cannot get any valid words of next level, cease the search
			if (nextLev.empty()) {
				return res;
			}
			
			currLev = nextLev;
			nextLev.clear();
		}
		
		// retrive results
		vector<string> currRes;
		retAllPaths(start, end, paths, currRes, res);
		return res;
    }
};

class CWordLadder: public BasicQue {
public:
	void doWork() {
		unordered_set<string> dict;
		dict.insert("hot");
		dict.insert("dot");
		dict.insert("dog");
		dict.insert("lot");
		dict.insert("log");
		Solution sln;
		string start = "hit",
			   end = "cog";
		//cout << sln.ladderLength(start, end, dict);
		vector<vector<string>> res = sln.findLadders(start, end, dict);
		for (int i = 0; i < res.size(); ++i) {
			for (int j = 0; j < res[i].size(); ++j) {
				cout << res[i][j] << ", ";
			}
			cout << endl;
		}
	}
};

#endif