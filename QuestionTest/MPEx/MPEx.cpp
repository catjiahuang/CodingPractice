// MPEx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cstdlib>
#include "omp.h"

void pooh(int id, double a[]) {}

int _tmain(int argc, _TCHAR* argv[])
{
// example 1
/*#pragma omp parallel
{
	int ID = omp_get_thread_num();
	printf("hello(%d) ", ID);
	printf("world(%d)\n", ID);
}*/

// example 2
/*
double A[1000];
omp_set_num_threads(4);
#pragma omp parallel
{
	int ID = omp_get_thread_num();
	pooh(ID, A);
}
	printf("all done\n");
*/

// example 3: calculate pi by integral
	static long num_steps = 100000;
	double step = 1.0/(double)num_steps;
	#define NUM_THREADS 2
	double pi = 0.0;
	omp_set_num_threads(NUM_THREADS);
/*
// solution 1
	int i, nthreads;
	double sum[NUM_THREADS];
	for (int i = 0; i < NUM_THREADS; ++i) sum[i] = 0.0f;
#pragma omp parallel
{
	int i, id, nthrds;
	double x;
	id = omp_get_thread_num();
	nthrds = omp_get_num_threads(); // deal with the case if only 1 thread is able to be created?
	if (id == 0) nthreads = nthrds;
	for (i = id, sum[id] = 0.0; i < num_steps; i = i + nthrds) {
		x = (i+0.5)*step;
		sum[id] += 4.0/(1.0+x*x);
	}
}
	for (int i = 0; i < nthreads; ++i) pi += sum[i] * step;
	
*/
/*
// solution 2
// prevent false sharing
#pragma omp parallel
{
	int i, id, nthrds;
	double x, sum = 0.0; // create a scalar (sum) local to accumulate partial sum
	id = omp_get_thread_num();
	nthrds = omp_get_num_threads();
	for (i = id, sum = 0.0; i < num_steps; i = i + nthrds) {
		x = (i+0.5)*step;
		sum += 4.0/(1.0+x*x);
	}
	#pragma omp critical
		pi += sum*step;
}
*/
/*
// solution 3
	int i;
	double x, sum = 0.0;
#pragma omp parallel for private(x) reduction(+:sum)
	for (i = 0; i < num_steps; ++i) {
		x = (i+0.5)*step;
		sum += 4.0/(1.0+x*x);
	}
	pi = step * sum;
*/
	printf("%f\n", pi);


	system("pause");
	return 0;
}