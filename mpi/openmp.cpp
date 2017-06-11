#include "bits/stdc++.h"
#include "omp.h"
using namespace std;
#define NUM_THREADS 4
#define MAX 20

int main(){
	printf("start\n");
	int t0=clock();
	int matrix[MAX];
	omp_set_num_threads(NUM_THREADS);
	long long sum=0;
	long long sumtmp[NUM_THREADS];
	#pragma omp parallel
	{
		int start,end;
		start=clock();
		double t1=omp_get_wtime();
		long i;
		long id=omp_get_thread_num();
		long long temp=0;
		for(i=id;i<MAX;i=i+NUM_THREADS){
			matrix[i]=i;
		}
		sumtmp[id]=temp;
		cout << id << endl;
		end=clock();
		double t2=omp_get_wtime();
		printf("%d,%d,t2=%lf,t1=%lf,parallel time=%f\n",end,start,t2,t1,(t2-t1));
	}
	for(int i=0;i<MAX;i++){
		cout << matrix[i] << endl;
	}
	for(long i=0;i<NUM_THREADS;i++){
		sum+=sumtmp[i];
	}
	printf("sum=%lld\n",sum);
	int t1,t2;
	sum=0;
	t1=clock();
	for(long i=1;i<=MAX;i++){
		sum+=i;
	}
	t2=clock();
	printf("sum=%lld\n",sum);
	printf("%d,%d,time=%d,pa time=%d\n",t2,t1,(t2-t1),t1-t0);
	return 0;
	
}
