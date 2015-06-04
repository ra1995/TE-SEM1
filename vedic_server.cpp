#include <iostream>
#include <sys/shm.h>
#include <sys/ipc.h>

using namespace std;

#define shm_sz 24

int main()
{
	key_t shm_key=5678;
	int num[2],send[4],sq;
	char *ptr,*shm;
	int shmid;

	shmid=shmget(shm_key,shm_sz,IPC_CREAT | 0666);
	shm=(char*)shmat(shmid,NULL,0);
	ptr=shm;

	while(true)
	{
		if(*ptr=='$')
		{
			num[0]=(int)*(ptr+1);
			num[1]=(int)*(ptr+2);
			cout<<num[0]<<num[1]<<" received.";
			break;
		}
	}
	sq=100*num[0];
	sq+=20*num[0]*num[1];
	sq+=num[1]+num[1];
	cout<<"\n"<<sq;

	send[0]=sq/1000;
	send[1]=(sq%1000)/100;
	send[2]=(sq%100)/10;
	send[3]=sq%10;
	cout<<"\n"<<send[0]<<send[1]<<send[2]<<send[3];

	*(ptr+1)=(char)send[0];
	*(ptr+2)=(char)send[1];
	*(ptr+3)=(char)send[2];
	*(ptr+4)=(char)send[3];
	*ptr='%';

	while(true)
	{
		if(*ptr=='#')
			break;
	}

	return 0;
}

