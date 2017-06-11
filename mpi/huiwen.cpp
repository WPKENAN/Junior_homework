#include <stdio.h>  
#include <stdlib.h>  
#include <omp.h>  
#include <unistd.h>  
#include <math.h>  
  
#define NUM_DATA 20000000  
#define THREAD_COUNT 4  
  
unsigned int data[NUM_DATA];  
/* Any faster methods ? */  
bool is_reversible(unsigned int n)  
{  
    int digits[16], m=n, i=0, j;  
    do{  
        digits[i++] = m % 10;  
        m /= 10;  
    }while(m > 0);  
    j = i >> 1;  
    while(n>0 && i>j){  
        if(digits[--i] != n % 10)  
            return false;  
        n /= 10;  
    }  
    return true;  
}  
 
void parallel_find()  
{  
    int rev_data = 0;  
#pragma omp parallel shared(rev_data)  
    {  
#pragma omp for  
        for(int i=0; i<NUM_DATA; i++)  
            if(is_reversible(data[i]))  
#pragma omp critical  
                rev_data ++;  
#pragma omp master  
        printf("rev: %u\n", rev_data);  
    }  
}  



int main(){  
    /* Give me more process priority */  
    nice(-20);  
    srand(0);  
#ifdef OPENMP  
    omp_set_num_threads(THREAD_COUNT);  
#endif  
      
    /* Randomize test data */  
    printf("Generating random numbers...\n");  
    for(int i=0; i<NUM_DATA; i++)  
        data[i] = rand();  
      
    for(int j=0; j<10; j++)  
        parallel_find();  
  
    return 0;  
} 
