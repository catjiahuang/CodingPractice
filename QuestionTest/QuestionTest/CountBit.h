#ifndef __CountBit_h__
#define __CountBit_h__

#include "BasicQue.h"

class CCountBit: public BasicQue {
public:
	void doWork() {
		char n = 3;
		cout << CountBit(n);
	}
	int CountBit(char n) {
		int count = 0;
		while (n) {
			count += n & 0x1;
			n >>= 1;
		}
		return count;
	}
	int CountBit2(char v) {
		int count = 0;
		while (v) {
			v &= (v - 1);
			count++;

		}
		return count;
	}
};


#endif