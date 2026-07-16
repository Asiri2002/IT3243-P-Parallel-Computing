#include<mpi.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define n 10

int main() {
	int np, pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int chunk = n / np;

	if (pid == 0) {
		int A[n];
		int local_max = A[0];
		for (int i = 0; i < n; i++) {
			A[i] = rand();
		}
		for (int i = 1; i < np; i++) {
			MPI_Send(&A[i * chunk], chunk, MPI_INT, i, 50, MPI_COMM_WORLD);
		}
		for (int i = 0; i < chunk; i++) {
			A[i];
			if (local_max < A[i]) {
				local_max = A[i];
			}
		}
		printf("local max: %d \n", local_max);
		for (int i = 1; i < np; i++) {
			MPI_Recv(&local_max, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
		}
		int local_max1 = local_max;
		if (local_max1 < local_max) {
			printf("maximum number: %d \n", local_max);
		}
		else {
			printf("maximum number: %d \n", local_max1);
		}
	}
	else {
		int B[n];
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		int local_max = B[0];
		for (int i = 0; i < chunk; i++) {
			B[i];
			if (local_max < B[i]) {
				local_max = B[i];
			}
		}
		printf("local max: %d \n", local_max);
		MPI_Send(&local_max, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;
}