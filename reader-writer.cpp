#include <iostream>
#include <omp.h>

using namespace std;

int A[10];
omp_lock_t my_lock;

void reader(int n)
{
	omp_set_lock(&my_lock);
	cout<<"\nReader "<<n<<" locked\n";
	cout<<A[n%10];
	cout<<"\nReader "<<n<<" unlocked\n";
	omp_unset_lock(&my_lock);
}

void writer(int n)
{
	omp_set_lock(&my_lock);
	cout<<"\nWriter "<<n<<" locked\n";
	A[n%10]=n;
	cout<<"\nWriter "<<n<<" unlocked\n";
	omp_unset_lock(&my_lock);
}

int main()
{
	int n;
	cout<<"Enter no of threads :";
	cin>>n;

#pragma omp parallel num_threads(n)
	{
		omp_init_lock(&my_lock);
		int i=omp_get_thread_num();
		writer(i);
		reader(i);
	}
	return 0;
}

