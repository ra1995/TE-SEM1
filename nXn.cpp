#include <iostream>
#include <stdlib>
#include <time.h>

using namespace std;
#define SIZE 8

__global__ void matmul(int *d_A,int *d_B, int *d_C)
{
	int x=threadIdx.x;
	int y=threadIdx.y;
	
	if(x>=SIZE || y>=SIZE)
		return;
	
	int value =0;
	for(int i=0;i<SIZE;i++)
	{
		int num1=d_A[(SIZE*y)+i];
		int num2=d_B[x+(SIZE*i)];
		value=value+(num1*num2);
	}
	
	d_C[x+(SIZE*y)]=value;
}

void matinit(int *A)
{
	srand(time(NULL));	
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			int num=rand()%100+1;
			A[i+(SIZE*j)]=num;
		}
	}
}

void disp(int *A)
{
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			cout<<A[i+(SIZE*j)]<<"\t";
		}
		cout<<"\n";
	}
}

int main()
{
	int *A,*B,*C;
	int *d_A,*d_B,*d_C;
	
	A=(int *)malloc(SIZE*SIZE*sizeof(int));
	B=(int *)malloc(SIZE*SIZE*sizeof(int));
	C=(int *)malloc(SIZE*SIZE*sizeof(int));
	cudaMalloc(&d_A,SIZE*SIZE*sizeof(int));
	cudaMalloc(&d_B,SIZE*SIZE*sizeof(int));
	cudaMalloc(&d_C,SIZE*SIZE*sizeof(int));
	
	matinit(A);
	matinit(B);
	cout<<"\n";
	disp(A);
	cout<<"\n";
	disp(B);
	
	cudaMemcpy(d_A,A,SIZE*SIZE*sizeof(int),cudaMemcpyHostToDevice);
	cudaMemcpy(d_B,B,SIZE*SIZE*sizeof(int),cudaMemcpyHostToDevice);
	
	dim3 threadsPerBlock(SIZE,SIZE);
	matmul<<<1,threadsPerBlock>>>(d_A,d_B,d_C);
	
	cudaThreadSynchronize();
	cudaMemcpy(C,d_C,SIZE*SIZE*sizeof(int),cudaMemcpyDeviceToHost);
	
	cout<<"\nResult :\n";
	disp(C);
	return 0;
}
