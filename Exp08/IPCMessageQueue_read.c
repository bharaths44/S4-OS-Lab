#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
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

	msgrcv(msgid,&message,sizeof(message),1,0);
	printf("THE DATA RECIEVED IS:	%s\n",message.msg_text);
	
	msgctl(msgid,IPC_RMID,NULL);	
}
