#include <stdio.h>  
#include <malloc.h>
#include "bits/stdc++.h" 
using namespace std;
#define SIZE 100 
  
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
  
int main()  
{  
    int *matrix[SIZE];  
    for (int i = 0; i < SIZE; i++)  
    {  
        matrix[i] = (int* )malloc( SIZE*sizeof(int) );  
    }  
	
	double start,end;
	start=clock();  
	#pragma omp parallel for
		for (int x = 0 ;x <SIZE; x++)  
		{  
		    for (int y =0;y <SIZE;y++)  
		    {  
		        double xv = ((double)x -(SIZE/2)) / (SIZE/4);  
		        double yv = ((double)y -(SIZE/2)) / (SIZE/4);  
		        matrix[x][y] = inSet(xv,yv);  
		    }  
		}  
	  
		for (int x =0; x<SIZE;x++)  
		{  
		    for (int y =0;y<SIZE;y++)  
		    {  
		        if (matrix[x][y] == -7)  
		        {  
		            printf(" ");  
		        }  
		    }  
		}
	end=clock();
	cout <<   end-start << endl;
    return 0;  
} 
