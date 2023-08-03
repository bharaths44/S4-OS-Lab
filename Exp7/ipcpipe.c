#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdlib.h>


int main()
{
	int fd[2],n;
	char buffer[100],as[100];
	pid_t p;
	pipe(fd);
	p=fork();


	if(p>0)
	{
		printf("Parent pass value to child \n");
		printf("Enter data :");
		fgets(as,100,stdin);
		write(fd[1],as,100);
	}

	
	read(fd[0],buffer,100);
	printf("Child receive data ");
	printf("\nBuffer :%s",buffer);
	return 0;
}
		
