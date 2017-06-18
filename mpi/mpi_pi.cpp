#include "bits/stdc++.h"
#include "mpi.h"
using namespace std;
#define PI 3.141592653589793238462643
//#define N 1e6
double f(double x){
	return (4.0/(1.0+x*x));
}
int main(int argc,char *argv[]){
	MPI_Comm comm=MPI_COMM_WORLD;
	int n=0,rank,size,i;
	double mypi,pi,h,sum,x;
	double startwtime,endwtime;

	MPI_Init(&argc,&argv);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	
	if(rank==0){
		cout << "请输入分割块数:" ;
		cin >> n;
		startwtime=MPI_Wtime();
	}
	MPI_Bcast(&n,1,MPI_INT,0,comm);
	
	h=1.0/(double)n;
	sum=0.0;
	for(i=rank+1;i<=n;i+=size){
		x=h*((double)i-0.5);
		sum+=f(x);
	}
	mypi=h*sum;
	MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,comm);

	if(rank==0){
		cout << setprecision(16) <<  "pi is " << pi << endl;
		cout << "Error is " << fabs(pi-PI) << endl;
		endwtime=MPI_Wtime();
		cout << "wall clock time = " << (endwtime-startwtime)*1000 << "ms" << endl;
	}
//	cout << rank << n << endl;
	MPI_Finalize();
	return 0;
		
}
