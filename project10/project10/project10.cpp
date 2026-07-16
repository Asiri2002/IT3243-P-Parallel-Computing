#include<mpi.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#define N 400

int main() {
	int pid, np;
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int A[N];
	int local_n = N / np;
	int B[N];

	if (pid == 0) {
		for (int i = 0; i < N; i++) {
			A[i] = i + 1;
		}
		for (int i = 1; i < np; i++) {
			MPI_Send(&A[local_n * i], local_n, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("process id: %d send message: %d \n", pid, A[i]);
		}
	}
	else {
		MPI_Recv(B, local_n, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < local_n; i++) {
			printf("process id: %d recv message: %d \n", pid, B[i]);
		}
	}
	MPI_Finalize();
	return 0;
}
