#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace std;

#define shm_sz 24

int main()
{
	key_t shm_key=5678;
	int num;
	char n[2];
	char *shm,*ptr;
	int shmid;

	shmid=shmget(shm_key,shm_sz,IPC_CREAT | 0666);
	shm=(char*)shmat(shmid,NULL,0);

	cout<<"\nEnter a 2 digit number :";
	cin>>num;
	n[0]=(char)num/10;
	n[1]=(char)num%10;
	ptr=shm;
	*(ptr+1)=n[0];
	*(ptr+2)=n[1];
	cout<<"\n"<<(int)*(ptr+1)<<(int)*(ptr+2)<<" sent to server.";
	*ptr='$';

	while(true)
	{
		if(*ptr=='%')
		{
			cout<<"\nSquare of number :"<<(int)*(ptr+1)<<(int)*(ptr+2)<<(int)*(ptr+3)<<(int)*(ptr+4)<<"\n";
			*ptr='#';
			break;
		}
	}

	return 0;
}

