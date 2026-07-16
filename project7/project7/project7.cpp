#include<mpi.h>
#include<stdio.h>
#include<string.h>
#define N 400

int main() {
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int local_n = N / np;
	int local_sum = 0;
	int local_sum1 = 0;
	int local_sum2 = 0;
	int global_sum = 0;

	if (pid == 0) {
		int A[N];
		for (int i = 0; i < N; i++) {
			A[i] = i + 1;
		}
		for (int i = 1; i < np; i++) {
			MPI_Send(&A[i * local_n], local_n, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("send message: %d process id: %d \n", A[i], pid);
		}
		for (int i = 0; i < local_n; i++) {
			A[i];
			local_sum = local_sum + A[i];
		}
		printf("%d \n", local_sum);
		for (int i = 1; i < np; i++) {
			MPI_Recv(&local_sum1, 1, MPI_INT, i, 50, MPI_COMM_WORLD, &sta);
			printf("recv message: %d process id: %d \n", local_sum1, pid);
			local_sum2 = local_sum2 + local_sum1;
		}
		global_sum = local_sum2 + local_sum;
		printf("global sum: %d \n", global_sum);

	}
	else {
		int B[N];
		MPI_Recv(B, local_n, MPI_INT, 0, 50, MPI_COMM_WORLD,&sta);
		for (int i = 0; i < local_n; i++) {
			printf("recieve message: %d process id: %d \n", B[i], pid);
			local_sum = local_sum + B[i];
		}
		printf("%d \n", local_sum);

		MPI_Send(&local_sum, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		printf("send total: %d process id: %d \n", local_sum, pid);
	}
	MPI_Finalize();
	return 0;
}