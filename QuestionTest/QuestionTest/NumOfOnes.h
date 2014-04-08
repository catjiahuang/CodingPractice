#ifndef __NumOfOnes_h__
#define __NumOfOnes_h__

#include "BasicQue.h"

class CNumOfOnes: public BasicQue {
public:
	void doWork() {
		int n = 123;
		cout << NumOfOnes(n);
	}
	int NumOfOnes(int n) {
		int sum = 0;
		int factor = 1;
		int currN = n;
		while (currN) {
			int upperBit = n / (factor * 10);
			int currBit = (n / factor) % 10;
			int lowerBit = n % factor;
			switch (currBit) {
				case 0:
					sum += upperBit * factor;
					break;
				case 1:
					sum += upperBit * factor + lowerBit + 1;
					break;
				default:
					sum += (upperBit + 1) * factor;
					break;
			}
			factor *= 10;
			currN /= 10;
		}
		return sum;
	}
};

#endif