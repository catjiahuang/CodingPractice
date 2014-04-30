#ifndef __BasicQueExp_h__
#define __BasicQueExp_h__

#include "BasicQue.h"
#include <vector>
#include <iostream>

using namespace std;

class CByteVal: public BasicQue {
public:
	int read(char *input, int pos) {
		int id = pos*12;
		int b_id = id/8;
		int b_off = id%8;
		if (b_off == 0) {
			int full = input[b_id];
			int half = input[b_id+1] >> 4;
			return full*16 + half;
		}
		else {
			int half = input[b_id] & 15;
			int full = input[b_id+1];
			return half*256 + full;
		}
	}
	void doWork() {
		char input[] = "123456";
		cout << read(input, 1) << endl;
		char c = '1';
		c = (c << 4) >> 4;
		cout << c << endl;
		//c = c >> 4;
		//cout << c;
	}
};

#endif