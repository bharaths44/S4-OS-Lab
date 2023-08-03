#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#define MAX 100

struct msg_buffer
{
	long msg_type;
	char msg_text[100];
}message;


void main()
{
	key_t key;
	int msgid;


	key=ftok("progfile",65);
	msgid=msgget(key,0666 | IPC_CREAT);


	message.msg_type=1;
	printf("Write the data to be sent:");
	fgets(message.msg_text,MAX,stdin);


	msgsnd(msgid,&message,sizeof(message),0);
	printf("THE DATA SENT IS:	%s\n",message.msg_text);
}
