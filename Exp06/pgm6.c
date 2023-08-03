#include <stdio.h>
#include <stdlib.h>

struct process {
    int pid;
    int at;
    int wt;
    int tat;
    int bt;
    int bt_print;
    int ct;
    int scheduled;
} p[20], temp;

int n, tq, time_units = 0, tail = -1, head = -1, ready_queue[20];
float total_wt = 0, total_tat = 0, avg_wt, avg_tat;

void push(int idx) {
    if (tail == 19) {
        printf("Queue is full!\n");
        exit(0);
    }
    if (head == -1)
        head = 0;
    tail = (tail + 1) % 20;
    ready_queue[tail] = idx;
}

int pop() {
    if (head == -1) {
        printf("Queue is empty!\n");
        exit(0);
    }
    int idx = ready_queue[head];
    if (head == tail)
        head = tail = -1;
    else
        head = (head + 1) % 20;
    return idx;
}

void display_item(int i) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", p[i].pid, p[i].at, p[i].bt_print, p[i].ct, p[i].tat, p[i].wt);
}

void display() {
    int i;
    printf("Time quantum: %d\n", tq);
    printf("Process id\tArrival time\tBurst time\tCompletion time\tTurnaround time\t\tWaiting time\n");
    for (i = 0; i < n; i++) {
        display_item(i);
    }
    printf("Average waiting time: %f", avg_wt);
    printf("\nAverage turnaround time: %f\n", avg_tat);
}

void swap(int i, int j) {
    temp = p[i];
    p[i] = p[j];
    p[j] = temp;
}

void pid_sort() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].pid > p[j].pid)
                swap(i, j);
        }
    }
}

void at_sort() {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at)
                swap(i, j);
        }
    }
}

int execute(int i) {
    int time = 0;
    if (p[i].bt > tq) {
        time = tq;
        p[i].bt -= tq;
    } else {
        time = p[i].bt;
        p[i].bt = 0;
        p[i].ct = time_units + time;

        //Calculate TAT and WT
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt_print;
        total_tat += p[i].tat;
        total_wt += p[i].wt;
    }
    time_units += time;
    return time;
}

void add_newly_arrived_tasks() {
    int i;
    for (i = 0; i < n; i++) {
        if (p[i].bt == 0)
            continue;
        if (p[i].at <= time_units && p[i].scheduled == 0) {
            push(i);
            p[i].scheduled = 1;
        }
    }
}

void rr() {
    int current_task, time;
    at_sort();
    push(0);
    p[0].scheduled = 1;
    while (head != -1) {
        current_task = pop();
        time = execute(current_task);
        add_newly_arrived_tasks();
        if (p[current_task].bt > 0)
            push(current_task);
    }
    avg_tat = total_tat / n;
    avg_wt = total_wt / n;
    pid_sort();
    printf("\nRound Robin algorithm\n");
    display();
}

int main() {
    int i;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &tq);
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter the arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].at);
        printf("Enter the burst time of process %d: ", i + 1);
        scanf("%d", &p[i].bt_print);
        p[i].bt = p[i].bt_print;
        p[i].scheduled = 0;
    }
    rr();
    return 0;
}

