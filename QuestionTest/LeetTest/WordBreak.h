#ifndef __ReorderList_h__
#define __ReorderList_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <string>
#include <unordered_set>

using namespace std::tr1;

class Solution {
public:
	// too slow
    /*vector<string> wordBreak(string s, unordered_set<string> &dict) {
        vector<string> res;
		if (dict.empty())
			return res;
		string resStr;
		int id = 0;
		int min_len = INT_MAX, max_len = 0;
		for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
			if (it->size() > max_len)
				max_len = it->size();
			if (it->size() < min_len)
				min_len = it->size();
		}
		wordBreakWork(res, resStr, s, id, dict, min_len, max_len);
		return res;
    }
	void wordBreakWork(vector<string> &res, string &resStr, string &s, int &id, unordered_set<string> &dict, int min_len, int max_len) {
		if (id == s.size()) {
			if (!resStr.empty()) {
				resStr = resStr.substr(0, resStr.size() - 1); // eleminate the last " "
				res.push_back(resStr);
			}
			return;
		}
		for (int i = min_len; i <= max_len && id + i - 1 < s.size(); ++i) {
			if (dict.find(s.substr(id, i)) != dict.end()) {
				string newStr = resStr + s.substr(id, i) + " ";
				int newId = id + i;
				wordBreakWork(res, newStr, s, newId, dict, min_len, max_len);
			}
		}
	}*/
	
	// use dynamic programming to prone not possible matching subsequences.
	bool wordBreak2(string s, unordered_set<string> &dict) {
		if (dict.empty())
			return false;
		string resStr;
		int id = 0;
		int min_len = INT_MAX, max_len = 0;
		for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
			if (it->size() > max_len)
				max_len = it->size();
			if (it->size() < min_len)
				min_len = it->size();
		}
		unordered_set<string> unmat;
		return wordBreakWork2(s, id, unmat, dict, min_len, max_len);
    }

	bool wordBreakWork2(string &s, int &id, unordered_set<string> &unmat, 
		unordered_set<string> &dict, int min_len, int max_len) {
		if (id == s.size()) {
			if (s.size() > 0) {
				return true;
			}
		}
		//for (int i = min_len; i <= max_len && id + i - 1 < s.size(); ++i) {
		for (int i = max_len; i >= min_len; --i) {
			if (id + i - 1 < s.size()) {
				if (dict.find(s.substr(id, i)) != dict.end()) {
					int newId = id + i;
					if (unmat.find(s.substr(newId)) != unmat.end())
						continue;
					if (wordBreakWork2(s, newId, unmat, dict, min_len, max_len))
						return true;
					else
						unmat.insert(s.substr(newId));
				}
			}
		}
		return false;
	}

	vector<string> wordBreak3(string s, unordered_set<string> &dict) {
		vector <string> res;
		if (dict.empty())
			return res;
		string resStr;
		int id = 0;
		int min_len = INT_MAX, max_len = 0;
		for (unordered_set<string>::iterator it = dict.begin(); it != dict.end(); it++) {
			if (it->size() > max_len)
				max_len = it->size();
			if (it->size() < min_len)
				min_len = it->size();
		}
		unordered_set<string> unmat;
		wordBreakWork3(res, resStr, s, id, unmat, dict, min_len, max_len);
		return res;
    }

	bool wordBreakWork3(vector<string> &res, string &resStr, string &s, int &id, unordered_set<string> &unmat, 
		unordered_set<string> &dict, int min_len, int max_len) {
		if (id == s.size()) {
			if (resStr.size() > 0) {
				resStr = resStr.substr(0, resStr.size() - 1); // eliminate the last " "
				res.push_back(resStr);
				return true;
			}
			return false;
		}
		//for (int i = min_len; i <= max_len && id + i - 1 < s.size(); ++i) {
		bool findRes = false;
		for (int i = max_len; i >= min_len; --i) {
			if (id + i - 1 < s.size()) {
				if (dict.find(s.substr(id, i)) != dict.end()) {
					int newId = id + i;
					if (unmat.find(s.substr(newId)) != unmat.end())
						continue;
					string newStr = resStr + s.substr(id, i) + " ";
					if (wordBreakWork3(res, newStr, s, newId, unmat, dict, min_len, max_len))
						findRes = true;
					else
						unmat.insert(s.substr(newId));
				}
			}
		}
		return findRes;
	}
};

class CWordBreak: public BasicQue {
public:
	void doWork() {
		unordered_set <string> dict;
		dict.insert("cat");
		dict.insert("cats");
		dict.insert("and");
		dict.insert("sand");
		dict.insert("dog");
		Solution s;
		string str = "catsanddog";
		vector <string> res = s.wordBreak(str, dict);
		for (int i = 0; i < res.size(); ++i) {
			cout << res[i] << endl;
		}
		
		res = s.wordBreak3(str, dict);
		for (int i = 0; i < res.size(); ++i) {
			cout << res[i] << endl;
		}
	}
};

#endif