//Zadatak 2: Napisati program koji nalazi sumu n celih brojeva koriscenjem ptp 
//komunikacije tako da svaki proces ucestvuje u sumiranju.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int value=0, sum=0, rank, size;
	MPI_Status status;
	
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0 && rank + 1 < size) {
		value = 1;
		MPI_Send(&value, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(&value, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);
		sum = value + rank + 1;
		if (rank < size - 1) {
			MPI_Send(&sum, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
		}
		if (rank == size - 1) {
			printf("Suma: %d", sum);
		}
	}

	MPI_Finalize();
	return 0;
}

