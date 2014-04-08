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

// Feel free to modify, correct, or remove any of the code included below to fit
// your own coding style.
#include "stdafx.h"
#include <cstring>
#include <cmath>
#include <cstdlib>

// set the max value x could be, so we can constraint the 
// range of prime numbers that needed to calculate
#define X_LIMIT_R 1000000000
#define PRIME_LIMIT X_LIMIT_R/2
#define X_LIMIT_TEST 60000000

struct pair
{
	unsigned int first;
	unsigned int second;
};

// Find and store all prime numbers that < x
bool isPrime[X_LIMIT_R/2];
int prime[X_LIMIT_TEST];
//bool isPrime[X_LIMIT_R/2];//bool isPrime[X_LIMIT_R]; // recored whehter a number is prime or not
//int* prime;//int prime[X_LIMIT]; // store found prime numbers
int prime_num = 0; // number of found prime numbers

void calcuAllPrimes() {
	memset(isPrime, 1, sizeof(isPrime)); // initallly set all numbers be prime
	int x = X_LIMIT_R;
	/*
	for (unsigned i = 0; i < x; i += 2) {
		isPrime[i] = 0; // exclude number of times of 2: all even numbers
	}
	isPrime[1] = 0; // exclude 1
	for (unsigned i = 3; ; i += 2) { // only consider odd numbers
		if (isPrime[i]) { // exclude all numbers that are the times of the number
			// numbers smaller than i * i have been excluded before, so just start from here
			// and only consider odd numbers afterwards, so step size is i * 2
			int j = i * i, k = i * 2;
			if (j >= x)
				break; // finish finding all primes
			while (j < x) {
				isPrime[j] = 0;
				j += k;
			}
		}
	}
	*/
	// even numbers are excluded
	isPrime[0] = 0; // exclude 1
	for (unsigned i = 1; ; ++i) {
		if (isPrime[i]) {
			int v = i * 2 + 1;
			int j = v * v, k = v * 2;
			if (j >= x)
				break;
			while (j < x) {
				isPrime[(j - 1)/2] = 0;
				j += k;
			}
		}
	}

	int t = 0;
	for (unsigned i = 0; i < x/2; ++i) {
		if (isPrime[i])
			t++;
	}
	// save all primes
	//prime = new int[t];
	prime[prime_num++] = 2; // store num 2
	/*for (unsigned i = 3; i < x; i += 2) {
		if (isPrime[i]) {
			prime[prime_num] = i;
			prime_num++;
		}
	}*/
	for (int i = 0; i < X_LIMIT_R/2; ++i) {
		if (isPrime[i]) {
			prime[prime_num] = i * 2 + 1;
			prime_num++;
		}
	}
}

// Find all the prime factors of x
//int p[X_LIMIT]; // prime factors
//int cnt[X_LIMIT]; // occurarnce count of each prime factor
int p[X_LIMIT_TEST];
int cnt[X_LIMIT_TEST];
int p_num = 0; // total number of types of prime factor

int calcuSum(int x) {
	// calculate the occurrance of each prime number
	memset(p, 0, sizeof(p));
	memset(cnt, 0, sizeof(cnt));
	p_num = 0;
	int v = x;
	for (unsigned i = 0; prime[i] <= v && i < prime_num; ++i) {
		int c = 0;
		while (v % prime[i] == 0) {
			c++;
			v /= prime[i];
		}
		if (c > 0) {
			p[p_num] = prime[i];
			cnt[p_num] = c;
			p_num++;
		}
	}
	if (v > 1) { // x is prime number itself
		p[0] = v;
		cnt[0] = 1;
		p_num = 1;
	}
	// calculate the sum, use the formula:
	// sum = (1 + a + ... a^c0) * (1 + b + .. + b^c1) * ...
	int sum = 1;
	for (unsigned i = 0; i < p_num; ++i) {
		//sum *= (1 - (int)pow((float)p[i], cnt[i] + 1)) / (1 - p[i]); // pow not give precise result
		int e = 1;
		int m = 1;
		for (unsigned j = 0; j < cnt[i]; ++j) {
			e *= p[i];
			m += e;
		}
		sum *= m;
	}
	sum -= x;

	return sum;
}

void printRes(char* s, pair* pairs) {
	printf("%d %d ", pairs->first, pairs->second);
	printf(s);
	printf("\n");
}

void determine_aliquot_type(pair* pairs, unsigned n)
{
	calcuAllPrimes();

	int i = 0;
	while (i < n) {
		int pd = 0;
		bool found = false;
		// get pd length
		int v = pairs->first;
		while (v != 0) {
			v = calcuSum(v);
			pd++; // whenever calculate the sum, add 1 to period
			// test if A can change to B
			if (v == pairs->second) {
				if (pairs->first == pairs->second) {
					found = true;
					break;
				}
				// test if B can change back to A
				int v2 = pairs->second;
				while (v2 != 0) {
					v2 = calcuSum(v2);
					pd++;
					if (v2 == pairs->first) {
						found = true;
						break;
					}
					if (v2 == pairs->first)
						break;
				}
				if (found)
					break;
			}
			// if got loop, need to break
			if (v == pairs->first)
				break;
		}

		if (found) {
			if (pd == 1)
				printRes("perfect", pairs);
			else if (pd == 2)
				printRes("amicable", pairs);
			else
				printRes("sociable", pairs);
		}
		else
			printRes("nothing", pairs);

		pairs++;
		i++;
	}
}

int main(int argc, char* argv[])
{
	// TODO: generate your additional test cases here
	pair pairs[] = {
		{6, 6}, {28, 28}, {496, 496}, {8128, 8128}, // perfect pairs
		{220, 284}, {1184, 1210}, {2620, 2924}, {5020, 5564}, {6232, 6368}, // amicable pairs
		{14288, 14536}, {14316, 17716}, {28158165, 30853845}, {1264460, 1727636}, // socialble pairs
		{0, 0}, {220, 374}, {14316, 38271}, {1727636, 1272890}, // nothing
		{6, 10}, {2620, 2000}, {30853845, 20000000}, // nothing: with one number from meaningful pairs
		{220, 220}, {2924, 2924} // I classify these pairs as amicable, as they have period of 2... it's easy to categerize them to other types.
	}; 
	unsigned n = sizeof(pairs)/ sizeof(pair);

	determine_aliquot_type(pairs, n);

	system("pause");

	return 0;
}