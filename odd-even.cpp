#include <iostream>

using namespace std;

__global__ void odd(int *d_A,int SIZE)
{
	int i=threadIdx.x;
	int temp;
	if(i%2==1 && i<SIZE-1)
	{
		if(d_A[i]>d_A[i+1])
		{
			temp=d_A[i];
			d_A[i]=d_A[i+1];
			d_A[i+1]=temp;
		}
	}
}

__global__ void even(int *d_A,int SIZE)
{
	int i=threadIdx.x;
	int temp;
	if(i%2==0 && i<SIZE-1)
	{
		if(d_A[i]>d_A[i+1])
		{
			temp=d_A[i];
			d_A[i]=d_A[i+1];
			d_A[i+1]=temp;
		}
	}
}

int main()
{
	int *A,p,SIZE;
	int *d_A;
	
	cout<<"Enter size of array :";
	cin>>SIZE;
	cout<<"Enter elements :\n"
	A=(int *)malloc(SIZE*sizeof(int));
	for(int i=0;i<SIZE;i++)
	{
		cin>>A[i];
	}
	
	cudaMalloc(&d_A,SIZE*sizeof(int));
	cudaMemcpy(d_A,A,SIZE*sizeof(int),cudaMemcpyHostToDevice);
	
	if(SIZE%2==0)
		p=SIZE/2;
	else p=(SIZE/2)+1;
	
	for(int i=0;i<p;i++)
	{
		even<<<1,SIZE>>>(d_A,SIZE);
		if(i!=p-1)
			odd<<<1,SIZE>>>(d_A,SIZE);
		else if(i==p-1 && SIZE%2==0)
			odd<<<1,SIZE>>>(d_A,SIZE);
	}
	
	cudaMemcpy(A,d_A,SIZE*sizeof(int),cudaMemcpyDeviceToHost);
	cout<<"\nSORTED ARRAY :\n"
	for(int i=0;i<SIZE;i++)
		cout<<A[i]<<" ";
	
	free(A);
	cudaFree(d_A);
}
