#include <mpi.h>
#include <stdio.h>
#include <math.h>

int main(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);

	int sum = 0, MyRank=0, Source_tag, Destination_tag;
	int NoofLevels, Level, NextLevel, ilevel;
	int value = 0, Source = 0, Destination = 0;
	int Root = 0;
	MPI_Status status;

	int size;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

	sum = MyRank + 1;
	Source_tag = 0;
	Destination_tag = 0; 

	NoofLevels = (int)(log((double)size) / log(2.0));
	for (ilevel = 0; ilevel < NoofLevels; ilevel++) {
		Level = (int)(pow((double)2, (double)ilevel));
		if ((MyRank % Level) == 0) {
			NextLevel = (int)(pow((double)2, (double)(ilevel+1)));
			if ((MyRank % NextLevel) == 0) {
				Source = MyRank + Level;
				if (Source <= size - 1) {
					MPI_Recv(&value, 1, MPI_INT, Source, Source_tag,
						MPI_COMM_WORLD, &status);
					sum = sum + value;
					printf("%d partial sum: %d\n", MyRank, sum);
					fflush(stdout);
				}
			}
			else {
				Destination = MyRank - Level;
				MPI_Send(&sum, 1, MPI_INT, Destination, 
					Destination_tag, MPI_COMM_WORLD);
			}
		}
	}
	if (MyRank == Root)
		printf("%d Final SUM %d\n", MyRank, sum);

	MPI_Finalize();
	return 0;
}