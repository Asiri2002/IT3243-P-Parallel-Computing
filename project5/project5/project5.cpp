#include<mpi.h>
#include<stdio.h>
#include<string.h>

int main() {
	int np, pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;
	
	int sendm = 10;
	int recvm;
	if (pid == 0) {
			MPI_Send(&sendm, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
			printf("send message: %d process id: %d \n", sendm, pid);
			MPI_Recv(&recvm, 1, MPI_INT, np - 1, 50,
				MPI_COMM_WORLD, &sta);

			printf("recv message: %d process id: %d\n", recvm, pid);
	}
	else {
		MPI_Recv(&recvm, 1, MPI_INT, pid-1, 50, MPI_COMM_WORLD, &sta);
		printf("recv message: %d process id: %d \n", recvm, pid);
			if (pid == np-1) {
				MPI_Send(&sendm, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
				printf("send message: %d process id: %d \n", sendm, pid);
			}
			else {
				MPI_Send(&sendm, 1, MPI_INT, pid+1, 50, MPI_COMM_WORLD);
				printf("send message: %d process id: %d \n", sendm, pid);
			}
	}
	MPI_Finalize();
	return 0;
}