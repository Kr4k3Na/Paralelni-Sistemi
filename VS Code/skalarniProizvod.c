#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
	int product, partialProduct=0, rank, size;
	int* A = NULL, * B = NULL;
	int a=0, b=0;
	int n=0, chunk;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (rank == 0) {
		scanf_s("%d", &n);
		A = (int*)malloc(n * sizeof(int));
		B = (int*)malloc(n * sizeof(int));
		for (int i = 0; i < n; i++)
			scanf_s("%d%d", &A[i], &B[i]);
	}

	MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
	chunk = n / size;

	int* localA = malloc(chunk * sizeof(int));
	int* localB = malloc(chunk * sizeof(int));

	MPI_Scatter(A, chunk, MPI_INT, localA, chunk, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Scatter(B, chunk, MPI_INT, localB, chunk, MPI_INT, 0, MPI_COMM_WORLD);
	
	if (chunk == 0) {
		partialProduct = localA[0] + localB[0];
	}
	else {
		for (int i = 0; i < chunk; i++) {
			partialProduct += localA[i] * localB[i];
		}
	}

	MPI_Reduce(&partialProduct, &product, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	
	if (rank == 0) {
		printf("Final product is: %d\n", product);
		free(A);
		free(B);
	}

	MPI_Finalize();
	return 0;
}