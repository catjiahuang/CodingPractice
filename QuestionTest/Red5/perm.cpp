/*****************************************************************************
The Problem:

	Given the list of numbers 1, 2, 3, ..., n, we choose to list 
	permutations in numerical order. For example, with n=3, our list 
	would be:

	1,2,3
	1,3,2
	2,1,3
	2,3,1
	3,1,2
	3,2,1

	Given a value of n, the problem is to determine the kth permutation. 
	Thus, for n=3 (see above) and k=4, the corresponding permutation is 
	2,3,1.

	Write a function which (given values of n and k) produces the kth 
	permutation of the numbers 1 through n.

	Your solution will be evaluated on efficiency, coding style, readibility,
	and correctness. Please also include your test cases.

The Output:

	Print the permutation with each element separated by spaces on a line by itself. 
	Example: For the input n=3, k=4, the output would be:

	2 3 1

*****************************************************************************/


/*****************************************************************************
 *****************************************************************************
				          Solution Explanation
General Idea:
	1. Use k/(n-1)! can get the index of the first number to pick from the 
	ascending array 1, 2, 3 ... n.
	2. Once a number is picked, remove it from the ascending array, and then
	pick the next number of the index k'/(n'-1), where k'=k%(n-1)!, n'=n-1.
	Repeat this procedure until there is only one left, which turns to be the
	last selection.

Note:
	1. Since the inputs n and k are type of int. They need to be bounded by
	INT_MAX 2147483647. This limit on k decides that to the most 13 largest numbers
	in the ascending array will participate in the reordering in the end part, 
	while other smaller numbers will remain original order in the front part.
	2. This problem took me 1 hr for basic implementation, and another hr to think over
	and deal with the boundary conditions.
******************************************************************************/

#include "stdafx.h"
#include <vector>
//#include <cstdlib>

using namespace std;

// The maximal possible n
int max_n_limit = -1;

// Calculate the max n for full permutations
// Calculate once and retrieve multiple times
// The max number of permutation bits is max_n_limit + 1
int getMaxN() {
	if (max_n_limit == -1) {
		int v = INT_MAX;
		int d = 1;
		while(v > 0) {
			v /= d;
			d++;
		}
		max_n_limit = d - 2;
	}
	return max_n_limit; // max_n_limit will be 12
}

// Calculate the factorial(N!) of the given number
int getFactor(int n) {
	if (n > max_n_limit)
		return -1;
	int res = 1;
	for (unsigned i = 1; i <= n; ++i)
		res *= i;
	return res;
}

// Generate specific permutation with index k
void placer(int n, int k) {
	getMaxN();
	// check validity
	if (n < 1) {
		printf("Not valid n.\n");
		return;
	}
	// k is not valid, if it's larger than the number of all permutations
	if (k < 1 || !((n <= getMaxN() && k <= getFactor(n)) || n > getMaxN())) {
		printf("Not valid k.\n");
		return;
	}

	vector <int> rem; // stores the remaining numbers that haven't be used yet
					  // rem can be max_n_limit + 1 = 13 to the most
	int offset = n > (getMaxN() + 1) ? n - getMaxN() - 1 : 0; 
	for (unsigned i = 1; i <= min(n, getMaxN() + 1); ++i) {
		rem.push_back(i + offset); // store the largest numbers
	}

	k -= 1; // k starts from 1, to do indexing, need to subtract 1
	int p = 1; // for generating those numbers that don't participate in permutations
	while (n > 1) {
		int id = 0;
		int factor = getFactor(n-1);
		if (factor != -1) { // valid factorial with n-1 <= max_n_limit(12)
			id = k / factor;
			k %= factor;
			printf("%d ", rem[id]);
			// remove used number, the remaining numbers will still keep in ascending order
			int i = 0;
			for (vector <int>::iterator it = rem.begin(); it != rem.end(); ++it) {
				if (i == id) {
					rem.erase(it);
					break;
				}
				i++;
			}
		}
		else { // invalid factorial with n-1 > max_n_limit(12), 
			   // just use the ascending number in order
			printf("%d ", p);
			p++;
		}
		n--;
	}
	// there will be one number left, take it as the last one
	printf("%d\n", rem[0]);
}

// main entry point
int main(int argc, char* argv[]) {
	placer(3, 4);  // 2 3 1
	placer(10, 1); // 1 2 3 4 5 6 7 8 9 10
	placer(4, 24); // 4 3 2 1
	// TODO: generate your additional test cases here
	placer(4, 4); // 1 3 4 2
	placer(4, 6); // 1 4 3 2
	placer(3, 7); // Not valid k. Test too large k for n.
	placer(3, 0); // Not valid k. Test too small k.
	placer(0, 5); // Not valid n. Test too small n.
	placer(1, 1); // 1
	placer(1, 2); // Not valid k. Test too large k for n.
	placer(10, 3637); // 1 2 3 9 4 6 8 5 7 10
	placer(13, 2); // 1 2 3 4 5 6 7 8 9 10 11 13 12
	placer(12, 2); // 1 2 3 4 5 6 7 8 9 10 12 11
	placer(12, 479001600); // 12 11 10 9 8 7 6 5 4 3 2 1
	placer(12, 479001601); // Not valid k. Test too large k for n.
	placer(20, INT_MAX); // k reaches maximal
	placer(100, INT_MAX); // k reaches maximal
	//placer(1000, INT_MAX); // k reaches maximal
	//placer(INT_MAX, INT_MAX); // will take a while...
	
	//system("pause");

	return 0;
}