#ifndef __ValidPalin_h__
#define __ValidPalin_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
	bool isLetter(char c) {
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'))
			return true;
		return false;
	}
	bool isSameLetter(char c1, char c2) {
		if (c1 == c2 || (c1 >= 'a' && (c1 - ('a' - 'A') == c2)) || 
						(c2 >= 'a' && (c2 - ('a' - 'A') == c1))) return true;
		return false;
	}
    bool isPalindrome(string s) {
		int i = 0, j = s.length() - 1;
		while (i < j) {
			while (i <= s.length()-1 && !isLetter(s[i]))
				i++;
			while (j >= 0 && !isLetter(s[j]))
				j--;
			if (i >= j)
				break;
			if (!isSameLetter(s[i], s[j]))
				return false;
			i++;
			j--;
		}
		return true;
    }
};

class CValidPalin: public BasicQue {
public:
	void doWork() {
		Solution sln;
		string s = "1a2";//".,";//" ";//"";//"race a car";//"A man, a plan, a canal: Panama";
		cout << sln.isPalindrome(s);
	}
};

#endif