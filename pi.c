#include <stdio.h>
#include <omp.h>

static long num_steps = 100000000;
double step;
#define NUM_THREADS 8
	
int main(int argc, char **argv){

	step = 1.0/(double)num_steps;

	/* Serial Implimentaion */
	double x, pi, sum = 0.0; 	
	
	double a = omp_get_wtime();
	for(int i=0; i<num_steps; i++){
		x = (i+0.5)*step;
		sum += 4.0/(1.0 + x*x);
	}

	pi = step*sum;
	
	double b = omp_get_wtime();
	printf("%lf\n",pi);
	printf("Time :%lf\n",(b-a)*10);
	
	
	/* Parallel Implimentaion */
	int nthreads;
	double X, PI, SUM[NUM_THREADS];
	omp_set_num_threads(NUM_THREADS);	
	double c = omp_get_wtime();
	
	#pragma omp parallel
	{
		int i,id,nthrds;
		id = omp_get_thread_num();
		nthrds = omp_get_num_threads();
				 
		if(id == 0)	nthreads = nthrds;  //  Check how many threads we got
		
		for(i=id, SUM[id]=0.0; i<num_steps; i=i+nthrds){
			X = (i+0.5)*step;
			SUM[id] += 4.0/(1.0 + X*X);		
		}
	}
	int i;
	for(i=0, PI = 0.0; i<nthreads; i++)
		PI += step*SUM[i];
	
	double d = omp_get_wtime();
	printf("%lf\n",PI);
	printf("Time :%lf\n",(d-c)*10);	
}
