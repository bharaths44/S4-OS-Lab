#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<stdlib.h>
#include<sys/wait.h>


void child()
{
	printf("Hello !!\n");
}

void parent()
{
	printf("Main task\n");
}


int main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		child();
		exit(EXIT_SUCCESS);
	}
	else if(pid>0)
	{
		wait(NULL);
		parent();
	}
	else
		printf("Unable to execute\n");
	return EXIT_SUCCESS;
}

