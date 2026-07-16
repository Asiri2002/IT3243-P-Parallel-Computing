#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

int main(){
	int np;
	int pid;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &np);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Status sta;

	int A[6] = { 1,2,3,4,5,6 };
	int chunk = 6 / np;
	int B[6];
	int tot = 0;
	int rtot;
	int newtot = 0;
	int newtot1 = 0;
	int sum = 0;
	if (pid == 0) {
		for (int i = 1; i < np; i++) {
			MPI_Send(&A[i * chunk], chunk, MPI_INT, i, 50, MPI_COMM_WORLD);
		}
		for (int i = 0; i < chunk; i++) {
			tot = tot + A[i];
		}
		printf("%d \n", tot);
		MPI_Recv(&rtot, 1, MPI_INT, 1, 50, MPI_COMM_WORLD, &sta);
		printf("p1,p2 message: %d process id: %d \n", rtot, pid);
		int t = rtot;
		MPI_Recv(&rtot, 1, MPI_INT, 3, 50, MPI_COMM_WORLD, &sta);
		printf("p3,p4,p5 message: %d process id: %d \n", rtot, pid);
		int v = rtot;

		sum = tot + t + v;
		printf("all summation is: %d \n", sum);

	}
	else if (pid == 2) {
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < chunk; i++) {
			printf("recv message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		MPI_Send(&tot, 1, MPI_INT, 1, 50, MPI_COMM_WORLD);
		printf("tot message: %d process id: %d \n", tot, pid);
	}
	else if (pid == 1) {
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < chunk; i++) {
			printf("recv message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		MPI_Recv(&rtot, 1, MPI_INT, 2, 50, MPI_COMM_WORLD,&sta);

		newtot = rtot + tot;

		MPI_Send(&newtot, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
		printf("tot message: %d process id: %d \n", newtot, pid);
	}
	else if (pid == 5) {
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < chunk; i++) {
			printf("recv message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		MPI_Send(&tot, 1, MPI_INT, 4, 50, MPI_COMM_WORLD);
	}
	else if (pid == 4) {
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < chunk; i++) {
			printf("recv message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		MPI_Recv(&rtot, 1, MPI_INT, 5, 50, MPI_COMM_WORLD, &sta);
		
		newtot1 = rtot + tot;

		MPI_Send(&newtot1, 1, MPI_INT, 3, 50, MPI_COMM_WORLD);
	}
	else if (pid == 3) {
		MPI_Recv(B, chunk, MPI_INT, 0, 50, MPI_COMM_WORLD, &sta);
		for (int i = 0; i < chunk; i++) {
			printf("recv message: %d process id: %d \n", B[i], pid);
			tot = tot + B[i];
		}
		MPI_Recv(&rtot, 1, MPI_INT, 4, 50, MPI_COMM_WORLD, &sta);
		
		newtot1 = rtot + tot;

		MPI_Send(&newtot1, 1, MPI_INT, 0, 50, MPI_COMM_WORLD);
	}
	MPI_Finalize();
	return 0;

}