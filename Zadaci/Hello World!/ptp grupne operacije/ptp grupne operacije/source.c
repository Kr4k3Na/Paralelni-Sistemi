#include <stdio.h>
#include <mpi.h>

int main(int argc, char* argv[]) {

	struct {
		int value;
		int rank;
	}in, out;

	int rank;
	int root;

	MPI_Init(&argc, &argv);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	in.value = rank + 1;
	in.rank = rank;
	root = 5;

	MPI_Reduce(&in, &out, 1, MPI_DOUBLE_INT, MPI_MAXLOC, root, MPI_COMM_WORLD);
	if (rank == root) {
		printf("Proces:%d rank=%d maks=%d\n", rank, out.rank, out.value);
	}

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Reduce(&in, &out, 1, MPI_DOUBLE_INT, MPI_MINLOC, root, MPI_COMM_WORLD);
	if (rank == root) {
		printf("Process:%d rank=%d min=%d\n", rank, out.rank, out.value);
	}

	MPI_Finalize();
}