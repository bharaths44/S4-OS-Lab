#include<stdio.h>
#include<stdlib.h>

struct process
{
	int pid;
	int at;
	int wt;
	int tat;
	int bt;
	int ct;
}p[20],temp;

int n;

void asort()
{
	for(int i=0;i<n-1;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(p[i].at > p[j].at)
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
			
		}
	}
	for(int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++)
		{
			if(p[i].at == p[j].at)
			{
				if(p[i].pid > p[j].pid)
				{
					temp = p[i];
					p[i] = p[j];
					p[j] = temp;
				}
			}
		}
	}
}			
		
void fcfs()
{
	float sum1=0,sum2=0;
	asort();
	p[0].ct = p[0].at + p[0].bt;
	for(int i=0;i<n;i++)
	{
		if(p[i+1].at > p[i].ct)
			p[i+1].ct = p[i+1].bt;
		else
			p[i+1].ct	=	p[i].ct		+	p[i+1].bt;

			
		p[i].tat	=	p[i].ct		- 	p[i].at;
		sum1		= 	sum1		+ 	p[i].tat;
		p[i].wt		=	p[i].tat 	- 	p[i].bt;
		sum2		=	sum2		+	p[i].wt;
	}
	printf("------------------- FCFS --------------------\n");
	printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
	for(int i=0;i<n;i++)
	{
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid  , p[i].at , p[i].bt ,  p[i].ct ,  p[i].tat , p[i].wt);
	}
	printf("---------------------------------------------\n");
	printf("Average TAT :%f\n",(sum1/n));
	printf("Average waiting time :%f\n",(sum2/n));
}


void main()
{
	printf("Enter number of processes :");
	scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		printf("Enter the PID :");
		scanf("%d",&p[i].pid);
		printf("Enter the arrival time :");
		scanf("%d",&p[i].at);
		printf("ENter the burst time :");
		scanf("%d",&p[i].bt);
		printf("\n\n");
	}
	
	fcfs();
}
