/*****************************************************************************
								ALIQUOT SEQUENCES

	An aliquot part is a divisor of a number other than the number itself. For
	example, the aliquot divisors of 6 are 1, 2, and 3.

	For a number n, we define s(n) to be the sum of the aliquot parts of n. If
	we start at some number and apply s repeatedly, using the previous sum as
	the seed for the subsequent application of s, we will form a sequence:

	s(9) = 1 + 3 = 4
	s(4) = 1 + 2 = 3
	s(3) = 1
	s(1) = 0

	When n is bounded, these aliquot sequences either end at 0 or become periodic.

	1. If the sequence sums to itself (period of length 1), the number is known
	   as a perfect number.
	2. If the sequence reaches an alternating pair (period of length 2), it is
	   called an amicable pair.
	3. If the period length is greater than 2, the numbers in the sequence are
	   called sociable numbers.

The Problem:

	Given a pair of two non-zero integers, j and k, where j,k < 1,000,000,000, determine
	if the numbers are amicable or not.

The Output:

	Print the pair on a line by itself, with each element separated by spaces and
	followed by the words "nothing" or "amicable" for their respective type.
	Example: For the input j=220, k=284, the output would be:

	220 284 amicable

******************************************************************************/


/*****************************************************************************
 *****************************************************************************
				          Solution Explanation
General idea:
	1. Calculate all prime numbers below the maximal number in the pairs (j, k),
	the maximal number could reach 1,000,000,000 as required.
	2. For each number x in a pair, calculate the sum of aliquot parts by using
	formula: sum = ((1 + a + ... a^c0) * (1 + b + .. + b^c1) * ...) - x
	where a, b... are the prime factors for x, and c0, c1 are the times of 
	occurrences of a, b... when factorizing x.
	3. Iteratively apply step 2 on j and then its result, check if the result can
	transform to k. If yes, do the same thing to check if k can transform to j, while
	recording the period times. Categorize the result.

Note:
	1. Requires ~0.75G static memory.
	2. This problem took me about half day including doing the research and implemetation.
******************************************************************************/

#include "stdafx.h"
#include <cstring>
//#include <cstdlib>

// This sets the max value x could be, so we can constrain the 
// range of prime numbers that needed to calculate
// currently set to 10^8
// if set to 10^9 (as indicated in the instructions), the time 
// for calculating prime numbers will need several secs.
#define X_LIMIT 1000000000 // this is 10^9

// the upper bounds of the number of those prime numbers below X_LIMIT
#define PRIME_LIMIT (X_LIMIT + 1)/2 // 1/2*(10^9) upper bound by eliminating all even numbers
#define PRIME_LIMIT_RES 60000000 // 6*(10^7) precomputed upper bound of the number of prime numbers below 10^9

struct pair {
	unsigned int first;
	unsigned int second;
};


/*****************************************************************************/
// Find and store all prime numbers that below the give number
// Time complexity is nearly O(N)
bool isPrime[PRIME_LIMIT]; // max required static memory is about 1/2*(10^9)*1(byte)=0.5G
int prime[PRIME_LIMIT_RES]; // max required static memory is about 6*(10^7)*4(bytes)=0.24G
int prime_num = 0; // number of found prime nums

void calcuAllPrimes(int x) {
	int p_lmt = (x + 1)/2;
	memset(isPrime, 1, sizeof(isPrime)); // initially set all nums be prime
	// even nums are excluded
	isPrime[0] = 0; // exclude 1
	for (unsigned i = 1; ; ++i) {
		if (isPrime[i]) {
			int val = i * 2 + 1;
			int j = val * val, k = val * 2;
			if (j >= x) // means have found all prime nums
				break;
			while (j < x) {
				isPrime[(j - 1)/2] = 0;
				j += k;
			}
		}
	}
	// save all prime nums
	prime[prime_num++] = 2; // save 2
	for (int i = 0; i < p_lmt; ++i) {
		if (isPrime[i]) {
			prime[prime_num++] = i * 2 + 1;
		}
	}
}


/*****************************************************************************/
// Find all the prime factors of x, and calculate the sum of all factors
int calcuSum(int x) {
	// calculate the occurrence of each prime number
	// meanwhile, calculate the sum by formula:
	// sum = ((1 + a + ... a^c0) * (1 + b + .. + b^c1) * ...) - x
	int val = x;
	int sum = 1;
	for (unsigned i = 0; prime[i] <= val && i < prime_num; ++i) {
		int cnt = 0;
		while (val % prime[i] == 0) {
			cnt++;
			val /= prime[i];
		}
		if (cnt > 0) { // update the sum
			int e = 1;
			int m = 1;
			for (unsigned j = 0; j < cnt; ++j) {
				e *= prime[i];
				m += e;
			}
			sum *= m;
		}
	}
	if (val <= 1)
		sum -= x;
	// else x must be prime number itself, the sum will remain as 1
	
	return sum;
}

/*****************************************************************************/
// For easy formatting print the result
void printRes(char* s, pair* pairs) {
	printf("%d %d ", pairs->first, pairs->second);
	printf(s);
	printf("\n");
}

/*****************************************************************************/
// Determine aliquot type for each pair
void determine_aliquot_type(pair* pairs, unsigned n) {
	// calculate the max num from all pairs,
	// use it to restrict the range for calculating needed prime numbers
	int i = 0;
	int max_v = 0;
	pair* t_pairs = pairs;
	while (i < n) {
		if (t_pairs->first > max_v)
			max_v = t_pairs->first;
		if (t_pairs->second > max_v)
			max_v = t_pairs->second;
		t_pairs++;
		i++;
	}
	
	// calculate all prime numbers below max_v
	calcuAllPrimes(max_v);

	// identify each pair
	i = 0;
	while (i < n) {
		int pd = 0; // period length
		bool found = false;
		int v = pairs->first;
		// check if pairs->first can transform to pairs->second
		while (v != 0) {
			v = calcuSum(v);
			pd++; // whenever calculate the sum, increment period length
			if (v == pairs->second) {
				if (pairs->first == pairs->second) {
					found = true;
					break;
				}
				int v2 = pairs->second;
				// check if pairs->second can transform back to pairs->first
				while (v2 != 0) {
					v2 = calcuSum(v2);
					pd++;
					if (v2 == pairs->first) {
						found = true;
						break;
					}
					if (v2 == pairs->second) // v2 gets in loop, no need to proceed
						break;
				}
				if (found)
					break;
			}
			// pairs->first gets in loop, no need to proceed
			if (v == pairs->first)
				break;
		}
		if (found) {
			switch (pd) {
				case 1: printRes("perfect", pairs); break;
				case 2: printRes("amicable", pairs); break;
				default: printRes("sociable", pairs);
			}
		}
		else
			printRes("nothing", pairs);

		pairs++;
		i++;
	}
}

int main(int argc, char* argv[]) {
	// TODO: generate your additional test cases here
	pair pairs[] = {
		{6, 6}, {28, 28}, {496, 496}, {8128, 8128}, // perfect pairs
		{220, 284}, {1184, 1210}, {2620, 2924}, {5020, 5564}, {6232, 6368}, // amicable pairs
		{14288, 14536}, {14316, 17716}, {28158165, 30853845}, {1264460, 1727636}, // sociable pairs
		{0, 0}, {1, 1}, {220, 374}, {14316, 38271}, {1727636, 1272890}, // nothing
		{6, 10}, {2620, 2000}, {30853845, 20000000}, // nothing: with one number from 3 types of pairs which can cause loop
		{220, 220}, {2924, 2924} // I classify these pairs as amicable, as they have period of 2... it's easy to categorize them to other types.
		//,{837463287, 737287129} // enable this case will need more time for precomputing prime numbers
	}; 
	unsigned n = sizeof(pairs)/ sizeof(pair);
	determine_aliquot_type(pairs, n);

	//system("pause");

	return 0;
}