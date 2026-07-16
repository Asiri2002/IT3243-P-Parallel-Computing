#include<mpi.h>
#include<stdio.h>
#include<string.h>

int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	if (pid == 0) {
		int A[5] = { 1,2,3,4,5 };
		MPI_Send(&A, 5, MPI_INT, 1, 50, MPI_COMM_WORLD);
	}
	if (pid == 1) {
		int B[5];
		int sum = 0;
		MPI_Recv(&B, 5, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < 5; i++) {
			printf("recieve message: %d \n", B[i]);
			sum = sum + B[i];
		}
		printf("sum : %d ", sum);
	}
	MPI_Finalize();
	return 0;
}