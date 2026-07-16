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

	int A[8] = { 1,2,3,4,5,6,7,8 };
	int N = 8 / np;
	int B[8];
	int tot = 0;
	int recvtot;
	
	
	if (pid == 0) {
		for (int i = 1; i < np; i++) {
			MPI_Send(&A[i * N], N, MPI_INT, i, 50, MPI_COMM_WORLD);
			printf("send message: %d process id: %d \n", A[i], pid);
		}
		for (int i = 0; i < N; i++) {
			printf("recieve message: %d process id: %d \n", A[i], pid);
			tot = tot + A[i];
		}
		printf("%d \n", tot);
		MPI_Send(&tot, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("send message: %d process id: %d \n", tot, pid);
		MPI_Recv(&recvtot, 1, MPI_INT, np - 1, 50, MPI_COMM_WORLD, &sta);
		printf("recieve message: %d process id: %d \n", recvtot, pid);
		printf("recvtot: %d \n", recvtot);
	}
	else {
		MPI_Recv(B, N, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < N; i++) {
			printf("recieve message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		printf("%d \n", tot);
		int newtot = tot;
		MPI_Recv(&recvtot, 1, MPI_INT, pid-1, 50, MPI_COMM_WORLD, &sta);
		printf("recieve message: %d process id: %d \n", recvtot, pid);
		newtot = newtot + recvtot;
		printf("newtot: %d \n", newtot);
		if (pid == np - 1) {
			MPI_Send(&newtot, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
			printf("send message: %d process id: %d \n", newtot, pid);
		}
		else {
			MPI_Send(&newtot, 1, MPI_INT, pid + 1, 50, MPI_COMM_WORLD);
			printf("send message: %d process id: %d \n", newtot, pid);
		}
	}
	MPI_Finalize();
	return 0;
	

}