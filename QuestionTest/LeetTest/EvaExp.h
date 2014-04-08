#ifndef __EvaExp_h__
#define __EvaExp_h__

#include "BasicQue.h"
#include <string>
#include <stack>
#include <vector>
#include <sstream>

using namespace std;

class Solution {
public:
    int evalRPN(vector <string> &tokens) {
        stack<string> charStack;
		int i = 0;
		while (i < tokens.size()) {
			charStack.push(tokens[i]);
			i++;
			char c = *(charStack.top().c_str());
			const char* pc = charStack.top().c_str();
			if ((c == '+' || c == '-' || c == '*' || c == '/') && pc[1] == '\0') {
				charStack.pop();
				int a = atoi(charStack.top().c_str());
				charStack.pop();
				int b = atoi(charStack.top().c_str());
				charStack.pop();
				int res = 0;
				switch (c) {
					case '+':
						res = b + a;
						break;
					case '-':
						res = b - a;
						break;
					case '*':
						res = b * a;
						break;
					default:
						res = b / a;
				}
				stringstream ss;
				ss << res;
				charStack.push(ss.str());
			}
		}
		return atoi(charStack.top().c_str());
    }
};

class CEvaExp: public BasicQue {
public:
	void doWork() {
		Solution sol;
		vector <string> vs;
		/*vs.push_back("2");
		vs.push_back("1");
		vs.push_back("+");
		vs.push_back("3");
		vs.push_back("*");*/
		/*vs.push_back("4");
		vs.push_back("13");
		vs.push_back("5");
		vs.push_back("/");
		vs.push_back("+");*/
		vs.push_back("3");
		vs.push_back("-4");
		vs.push_back("+");
		cout << sol.evalRPN(vs);
	}
};

#endif