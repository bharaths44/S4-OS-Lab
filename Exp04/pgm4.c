#include <stdio.h>
#include <stdlib.h>

struct process
{
	int pid;
	int at;
	int wt;
	int tat;
	int bt;
	int ct;
} p[20], temp;
int n;

void swap(int i, int j)
{
	temp = p[i];
	p[i] = p[j];
	p[j] = temp;
}

void atSort()
{
	int i, j;
	for(i = 0; i < n - 1; i++)
		for(j = 0; j < n - i - 1; j++)
			if(p[j].at > p[j + 1].at)
				swap(j, j + 1);
}

void pidSort()
{
	int i, j;
	for(i = 0; i < n - 1; i++)
		for(j = 0; j < n - i - 1; j++)
			if(p[j].pid > p[j + 1].pid)
				swap(j, j + 1);
}

void btSort()
{
	int i,j;
	for(i = 0; i < n - 1; i++)
		for(j = 0; j < n - i - 1; j++)
			if(p[j].bt > p[j + 1].bt)
				swap(j, j + 1);
}

void main()
{
	int i, pct, sbt, loc, j, f, flag = 0;

	printf("Enter the number of processes: ");
	scanf("%d", &n);
	printf("\n");
	for(i = 0; i < n; i++)
	{
		p[i].pid = i ;
		printf("Enter the arrival time of process %d: ", i );
		scanf("%d",&p[i].at);
		printf("Enter the burst time of process %d: ", i );
		scanf("%d",&p[i].bt);
		printf("\n");
	}
	
	for(i = 0; i < n; i++)
	{
		if(p[i].at > 0)
			flag = 1;
	}

	if(flag == 1)
		atSort();
	else
		btSort();
	p[0].ct = p[0].at + p[0].bt;
	p[0].tat = p[0].ct - p[0].at;
	p[0].wt = p[0].tat - p[0].bt;
	for(i = 1; i < n; i++)
	{
		pct = p[i - 1].ct;
		sbt = 100;
		f = 0;
		for(j = i; j < n; j++)
		{
			if(p[j].at <= pct && p[j].bt < sbt)
			{
				f = 1;
				loc = j;
				sbt = p[j].bt;
			}
			if(f == 0)
			{
				if(p[j].at >= pct && p[j].bt < sbt)
				{
					loc = j;
					sbt = p[j].bt;
				}
			}
		}
		if(f == 1)
			p[loc].ct = pct + p[loc].bt;
		else
			p[loc].ct = p[loc].at + p[loc].bt;

		
		p[loc].tat =  p[loc].ct  - p[loc].at;
		p[loc].wt  =  p[loc].tat - p[loc].bt;
		swap(loc, i);

	}
	pidSort();
	printf("\nSJF:\n");
	printf("PID\tAT\tBT\tCT\tWT\tTAT\n");
	for(i = 0; i < n; i++)
		printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].wt, p[i].tat);
}