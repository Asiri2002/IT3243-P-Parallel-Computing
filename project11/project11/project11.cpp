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

	int A[32] = { 45,41,92,79,11,83,97,91,98,67,53,34,68,72,76,12,78,59,64,06,89,62,26,23,17,35,36,18,25,55,43,56 };
	int B[32] = { 05, 18, 96, 63, 23, 10, 42, 34, 58, 84, 35, 61, 51, 41, 01, 13,45, 22, 53, 44, 56, 96, 62, 71, 67, 72, 78, 46, 83,91,97,98 };
	int recv[8];
	if (pid == 0) {
		for (int i = 0; i < 32; i++) {
			A[i];
		}
		for (int i = 0; i < 32; i++) {
			B[i];
		}
	}
	MPI_Bcast(A, 1, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 32; i++) {
		printf("pid: %d recv: %d \n",pid, A[i]);
	}
	MPI_Scatter(B, 8, MPI_INT, recv, 8, MPI_INT, 0, MPI_COMM_WORLD);
	for (int i = 0; i < 8; i++) {
		printf("pid: %d recv: %d \n", pid, recv[i]);
	}
	MPI_Finalize();
	return 0;
}