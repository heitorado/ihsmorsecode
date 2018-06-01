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
	int N = 10000000;

	double x, y;
	int i;

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

	printf("O resultado é: %lf\n", result);

	return 0;
}