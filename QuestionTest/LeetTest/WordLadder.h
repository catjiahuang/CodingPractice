#ifndef __WordLadder_h__
#define __WordLadder_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <queue>
#include <unordered_set>
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
		cout << sln.ladderLength(start, end, dict);
	}
};

#endif