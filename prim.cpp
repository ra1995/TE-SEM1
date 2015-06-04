#include <iostream>
#include <omp.h>

using namespace std;

#define SIZE 5
int map[SIZE][SIZE]= { { 0, 2, 0, 6, 0 },{ 2, 0, 3, 8, 5 },{ 0, 3, 0, 0, 7 },{ 6, 8, 0, 0, 9 },{ 0, 5, 7, 9, 0 }};
int res[SIZE][SIZE];
int visited[SIZE];
int ctr=0;

int main()
{
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			res[i][j]=-1;
		}
	}

	for(int i=0;i<SIZE;i++)
	{
		visited[i]=0;
	}
	res[0][0]=0;
	visited[0]=1;
	ctr++;

	while(ctr<SIZE)
	{
		int pos=-1;
		int thread=-1;
		int weight=9999;
#pragma omp parallel num_threads(SIZE)
		{
			int n=omp_get_thread_num();
			if(visited[n]==1)
			{
				for(int i=0;i<SIZE;i++)
				{
#pragma omp critical
					if(map[n][i]<weight && map[n][i]!=0 && visited[i]==0)
					{
						pos=i;
						thread=n;
						weight=map[n][i];
					}
				}
			}
		}
		res[thread][pos]=weight;
		visited[pos]=1;
		ctr++;
	}

	cout<<"\nMST :\n";
	for(int i=0;i<SIZE;i++)
	{
		for(int j=0;j<SIZE;j++)
		{
			cout<<res[i][j]<<"\t";
		}
		cout<<"\n";
	}
	return 0;
}

