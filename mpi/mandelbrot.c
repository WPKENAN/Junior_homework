#include <stdio.h>  
#include <malloc.h>
#include "time.h"
#include "mpi.h"

//#include "bits/stdc++.h" 
//using namespace std;
#define SIZE 1000
int wp;
enum color{
	RED,GREEN,BLUE,YELLOW,
};

int inSet(double creal,double cimage)  
{  
    int iterations = 0;  
    double zreal=0,zimage=0;
	double freal=0,fimage=0;
    while ((freal*freal+fimage*fimage<4) && (iterations < 1000))  
    {  
		freal=zreal*zreal-zimage*zimage+creal;
		fimage=2*zreal*zimage+cimage;
		zreal=freal;
		zimage=fimage;
		iterations++;  
    }  
    return iterations;  
}  

int mpi(int argc,char *argv[]){
	double start,end;
//	printf("start_address:%lld\n",&start);
//	start=clock();
    int *matrix[SIZE];  
	double a,b;
	a=clock();
    for (int i = 0; i < SIZE; i++)  
    {  
        matrix[i] = (int* )malloc( SIZE*sizeof(int) );  
    }  
	
	int done=0,n,myid,numprocs,i;
	double mypi,pi,sum;
	double startwtime,endwtime;
	int namelen;
	char processor_name[MPI_MAX_PROCESSOR_NAME];
//	#pragma omp parallel for
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&myid);
	MPI_Get_processor_name(processor_name,&namelen);
//	printf("n---->%d\n",&n);
	if(myid==0){
		start=MPI_Wtime();
	}
	
		for (int x = myid ;x <SIZE; x=x+numprocs)  
		{  
		    for (int y =0;y <SIZE;y++)  
		    {  
		        double xv = ((double)x -(SIZE/2)) / (SIZE/4);  
		        double yv = ((double)y -(SIZE/2)) / (SIZE/4);  
		        matrix[x][y] = inSet(xv,yv);  
//				matrix[x][y]=myid+10;
		    }  
		}
//		printf("%lld",&matrix);
//		for (int x =0; x<SIZE;x++)  
//		{  
//		    for (int y =0;y<SIZE;y++)  
//		    {
//				if(matrix[x][y]>-1)
//		        printf("%d\n",matrix[x][y]);
//		    }  
//		}
	if(myid==0){
		end=MPI_Wtime();
		printf("time=%lfms\n",(end-start)*1000);
	}
//	printf("-----\n");
//	MPI_Barrier(MPI_COMM_WORLD);
//	for(int i=0;i<SIZE;i++){
//		for(int j=0;j<SIZE;j++){
//			printf("%d,%d,%d:%d ",myid,i,j,matrix[i][j]);
//		}
//		printf("\n");
//	}
	MPI_Finalize();
//	b=clock();
//	printf("%lf,%lf time: %lf\n",b,a,b-a);
//	exit(0);
	return 0;
}
  
int main(int argc,char *argv[])  
{
//	printf("start\n");  
	mpi(argc,argv);
//	printf("end2;\n");
    return 0;  
}
