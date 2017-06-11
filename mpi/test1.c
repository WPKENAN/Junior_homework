#include "stdio.h"
#include "time.h"
#include "stdlib.h"
//#include "bits/stdc++.h"
#include "omp.h"
//using namespace std;
#define NUM_THREADS 1
#define MAX 1000000000

int main(){
//	omp_set_num_threads(NUM_THREADS);
	long long sum=0;
	long long sumtmp[NUM_THREADS];
	clock_t t1=clock();
	#pragma omp parallel
	{
		long i;
		long id=omp_get_thread_num();
		long long temp=0;
		#pragma omp for
		for(i=0;i<=MAX;i++){
			temp+=i;
		}
		sumtmp[id]=temp;
	} 
	for(long i=0;i<NUM_THREADS;i++){
		sum+=sumtmp[i];
	}
	clock_t t2=clock();
	printf("sum=%lld\n",sum);
	printf("parallel time=%d\n",(t2-t1));

	sum=0;
	t1=clock();
	for(long i=1;i<=MAX;i++){
		sum+=i;
	}
	t2=clock();
	printf("sum=%lld\n",sum);
	printf("time=%d\n",(t2-t1));
	return 0;
	
}
