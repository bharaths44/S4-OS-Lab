#include<stdio.h>

void main() {
    int pno, rno, allo[20][20], max[20][20], need[20][20], avail[20], flag[20], safe[20], l = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &pno);
    printf("\nEnter the number of resources: ");
    scanf("%d", &rno);
    printf("\nEnter the allocation matrix:\n");
    for (int i = 0; i < pno; i++) {
        for (int j = 0; j < rno; j++) {
            scanf("%d", &allo[i][j]);
        }
    }
    printf("\nEnter the max matrix:\n");
    for (int i = 0; i < pno; i++) {
        for (int j = 0; j < rno; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    printf("\nEnter the available matrix:\n");
    for (int i = 0; i < rno; i++) {
        scanf("%d", &avail[i]);
    }

    for (int i = 0; i < pno; i++) {
        flag[i] = 0;  // Initialize all processes as not allocated
    }

    // Calculate the need matrix
    for (int i = 0; i < pno; i++) {
        for (int j = 0; j < rno; j++) {
            need[i][j] = max[i][j] - allo[i][j];
        }
    }

    printf("\nThe need matrix is:\n");
    for (int i = 0; i < pno; i++) {
        for (int j = 0; j < rno; j++) {
            printf("%d\t", need[i][j]);
        }
        printf("\n");
    }

    int count = 0;
    while (count < pno) {
        int found = 0;
        for (int i = 0; i < pno; i++) {
            if (flag[i] == 0) {
                int j;
                for (j = 0; j < rno; j++) {
                    if (need[i][j] > avail[j]) {
                        break;
                    }
                }
                if (j == rno) {
                    for (int k = 0; k < rno; k++) 
                        avail[k] += allo[i][k];

                    safe[count++] = i;
                    flag[i] = 1;
                    found = 1;
                }
            }
        }
        if (found == 0)
            break;  // No safe sequence found
    }

    if (count == pno) {
        printf("\nThe given system is safe.\n");
        printf("The safe sequence is: ");
        for (int i = 0; i < pno; i++) {
            printf("%d", safe[i]);
            if (i < pno - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
    } else {
        printf("\nThe system is not safe.\n");
    }
}

