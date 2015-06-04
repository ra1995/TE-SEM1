#include <iostream>
#include <omp.h>

using namespace std;
int ary[99];
int thread[99];
int no_of_threads;
int num;
int pos;

int cmp(int lb,int ub)
{
	if(num>=ary[lb] && num<=ary[ub])
		return 1;
	else return 0;
}

int main()
{
	int n,lb,ub;
	int found=-1;
	cout<<"Enter no of elements :";
	cin>>n;
	for(int i=0;i<n;i++)
	{
		ary[i]=i*2;
	}
	cout<<"Enter no of threads :";
	cin>>no_of_threads;
	cout<<"Enter no to search :";
	cin>>num;
	if(n%no_of_threads!=0)
	{
		int new_n=((n/no_of_threads)+1)*no_of_threads;
		for(int i=n;i<new_n;i++)
		{
			ary[i]=9999;
		}
		n=new_n;
		cout<<"New size :"<<n;
	}
	lb=0;
	ub=n-1;


	while(true)
	{
		int siz=ub-lb+1;
		if(siz%no_of_threads!=0)
		{
			siz=((siz/no_of_threads)+1)*no_of_threads;
			ub=lb+siz-1;
		}
		int div=siz/no_of_threads;
		cout<<"\nDivision size :"<<div<<"\n";

		if(div==1)
		{
#pragma omp parallel num_threads(no_of_threads)
		{
			int i=omp_get_thread_num();
			if(ary[lb+i]==num)
			{
				found=lb+i;
			}
		}
		break;
		}
		else
		{
#pragma omp parallel num_threads(no_of_threads)
		{
			int i=omp_get_thread_num();
			thread[i]=cmp(lb+(i*div),lb+((i+1)*div)-1);
			if(thread[i]==1)
				pos=i;
		}
		}

		int new_lb=lb+(pos*div);
		int new_ub=lb+((pos+1)*div)-1;
		lb=new_lb;
		ub=new_ub;
	}

	if(found==-1)
		cout<<"\nNot found";
	else cout<<"\nFound at position:"<<found;
	return 0;
}

