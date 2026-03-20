//Zadatak. Napisati program koji uzima podatke od nultog procesa i šalje ih svim 
//drugim procesima tako što proces i treba da primi podatke i pošalje ih procesu 
//i+1, sve dok se ne stigne do poslednjeg procesa. Unos podataka se završava
//nakon što se prenese negativna vrednost podatka.

#include <mpi.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
    int broj, rank, size;
    MPI_Status status;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    do {
        if (rank == 0) {
            scanf_s("%d", &broj);
            if (rank < size - 1) {
                printf("Proces 0 salje: %d\n", broj);
                MPI_Send(&broj, 1, MPI_INT, rank + 1, 19, MPI_COMM_WORLD);
            }
        }
        else {
            MPI_Recv(&broj, 1, MPI_INT, rank - 1, 19, MPI_COMM_WORLD, &status);
            printf("Proces %d primio: %d\n", rank, broj);
            if (rank < size - 1) {
                MPI_Send(&broj, 1, MPI_INT, rank + 1, 19, MPI_COMM_WORLD);
            }
        }
    } while (broj>=0);

    MPI_Finalize();
    return 0;
}