#ifndef __LookupWord_h__
#define __LookupWord_h__

// not compilable
#include "BasicQue.h"

class CLookupWord: public BasicQue {
public:
	void doWork() {
		
	}
	const char c[10][];
	const char len[10]; // number of corresponding chars for each num
	// use recursion
	void LookupWord(int *input, int *answer, int n, int i) {
		if (i == n) {
			for (int j = 0; j < n; ++j)
				cout << c[input[j]][answer[j]];
			return;
		}
		for (int j = 0; j < len[input[i]]; ++j) {
			answer[i]++;
			LookupWord(input, answer, n, i + 1);
		}
	}
	// use 
};

#endif