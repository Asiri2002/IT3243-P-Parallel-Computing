#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

int main() {
	int pid, np;


	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int sendm = 10;
	int recv;
	if (pid == 0) {
		for (int i = 1; i < np; i++) {
			MPI_Send(&sendm, 1, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("process id: %d send message: %d \n", pid, sendm);
		}
		MPI_Recv(&recv, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, &sta);
		printf("process id: %d recv message: %d \n", pid, recv);
	}
	else{
		MPI_Recv(&recv, 1, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		printf("process id: %d recv message: %d \n", pid, recv);
		if(pid == 1){
			MPI_Send(&sendm, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
			printf("process id: %d send message: %d \n", pid, sendm);
		}
	}
	MPI_Finalize();
	return 0;
}