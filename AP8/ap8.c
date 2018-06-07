#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <limits.h>

int main(void)
{
	srand(time(NULL));
	int nthreads, tid;
	unsigned long long int N;
	double error;
	double x, y;
	unsigned long long int i;

	printf("Insert error value: ");
	scanf("%lf", &error);
	N = 1 / (error * error);
	printf("N = %llu\n", N);
	double result=0.0;

	#pragma omp parallel private(x, y)
	{
		#pragma omp for 
		for (i=0; i<N; ++i){
			x = rand() / (double)RAND_MAX;
			y = rand() / (double)RAND_MAX;

			if( x*x + y*y <= 1)
			{
				#pragma omp critical
				{
					++result;
				}
			}
			
		}
	}

	result = (4*result)/N;

	printf("Result: %lf\n", result);

	return 0;
}
