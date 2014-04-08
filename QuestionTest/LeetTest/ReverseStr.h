#ifndef __ReverseStr_h__
#define __ReverseStr_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
		string res;
		int i = s.length()-1;
		while (i > 0 && s[i] == ' ')
			i--;
		while (i >= 0) {
			if (s[i] == ' ') {
				while(i >= 0 && s[i] == ' ')
					i--;
				if (i >= 0)
					res += ' ';
				else
					break;
			}
			res += s[i];
			i--;
		}
		i = 0;
		int h = 0, t = 0;
		while (i < res.length()) {
			h = i;
			while ((i + 1) < res.length() && res[i+1] != ' ') {
				i++;
			}
			t = i;
			while (h < t) {
				swap(res[h], res[t]);
				h++;
				t--;
			}
			i += 2;
		}
		s = res;
    }
};

class CReverseStr: public BasicQue {
public:
	void doWork() {
		Solution sln;
		string s = "o the sky is blue";//"the sky is blue";//" ";//"the sky is blue";//"o the sky is blue";//" the sky is blue";//" ";//"the";//"the sky is blue";
		sln.reverseWords(s);
		cout << s;
	}
};

#endif