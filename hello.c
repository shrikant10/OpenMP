#include <stdio.h>
#include <omp.h>

int main(){
	
	#pragma omp parallel
	{
	int ID = omp_get_thread_num();
	printf("\n Shrikant: %d ",ID);
	printf("\n Gupta : %d  ",ID);
	}
}
