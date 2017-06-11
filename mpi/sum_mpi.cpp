#include "bits/stdc++.h"
using namespace std;

double f(double a){
	return (4.0/(1.0+a*a));
}

int main(){
	int done=0,n,myid,numprocs,i;
	double mypi,pi,sum;
	double startwtime,endwtime;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];

	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(processor_name,&namelen);

	fprintf(stderr,"Process 5d on %s\n",myid,processor_name);
	fflush(stderr);

	n=0;
	while(!done){
		if(my_id==0){
			printf("Input a number :");fflush(stdout);
			scanf("%d"&n);

			startwtime=MPI_Wtime();
		}
		MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
		if(n==0){
			done=1;
		}
		else{
			sum=0.0;
			for(i=myid+1;i<=n;i+=numprocs){
				sum+=1;
			}
		}
		mypi=sum;
		MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
		if(myid==0){
			printf("result %1.6f\n",pi);
			endwtime=MPI_Wtime();
			printf("time=%f\n",endwtime-startwtime);
		}
	}
	MPI_Finalize();
}
