#include <stdio.h>
#include <mpi.h> /* For MPI functions, etc */
int main(int argc, char * argv[]){

	int rank, size;
	MPI_Init(&argc, &argv); /* MPI Initialization */
	MPI_Comm_rank(MPI_COMM_WORLD, &rank); /* Get id of current process */
	MPI_Comm_size(MPI_COMM_WORLD, &size); /* Get # of processes */
	printf("Hello world from process %d of %d\n", rank, size);
	MPI_Finalize(); /* MPI Finalization */
	return 0;
}
