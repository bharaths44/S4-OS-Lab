#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/shm.h>
#include<sys/ipc.h>

void main()
{
	int i;
	void *shared_memory;
	char buff[100];
	int shmid;

	key_t key = ftok("shmfile",65);
	
	shmid=shmget(key,1024,0666|IPC_CREAT);
	printf("key of shared memory is %d\n",shmid);

	shared_memory=shmat(shmid,NULL,0);
	printf("Data read from shared memory is %s",(char*)shared_memory);
}
