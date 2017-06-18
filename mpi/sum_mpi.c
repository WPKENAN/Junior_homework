#include "mpi.h"
#include "stdio.h"
#include "math.h"
#include "time.h"

double f(double a){
	return (4.0/(1.0+a*a));
}

int main(int argc,char *argv[]){
	int done=0,n,myid,numprocs,i;
	double mypi,pi,sum;
	double startwtime,endwtime;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	printf("start:\n");
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(processor_name,&namelen);

	MPI_Barrier(MPI_COMM_WORLD);
	fprintf(stderr,"Process %d on %s\n",myid,processor_name);
	fflush(stderr);

	n=200000000;

	double start,end;
	
	while(!done){
		if(myid==0){
			printf("Input a number :\n");fflush(stdout);
//			scanf("%d",&n);

			startwtime=MPI_Wtime();
			start=clock();
		}
//		MPI_Bcast(&n,1,MPI_INT,0,MPI_COMM_WORLD);
		if(n==0){
			done=1;
		}
		else{
			sum=0.0;
			for(i=myid+1;i<=n;i+=numprocs){
				sum+=i;
			}
		}
		mypi=sum;
		MPI_Reduce(&mypi,&pi,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
		if(myid==0){
			printf("result %.16f\n",pi);
			endwtime=MPI_Wtime();
			end=clock();
			printf("time=%f\n,%lf\n",endwtime-startwtime,end-start);
		}
		done=1;
	}
	MPI_Barrier(MPI_COMM_WORLD);
	printf("end;\n");
	MPI_Finalize();
}
