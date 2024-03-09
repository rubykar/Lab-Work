#include<stdio.h>
#include<stdlib.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, st;
    char pname[10];
} p[5];

void start_time() {
    p[0].st = p[0].at;
    for (int i = 1; i < 5; i++)
        p[i].st = p[i - 1].ct;
}

void completion_time() {
    for (int i = 0; i < 5; i++) {
        p[i].ct = p[i].st + p[i].bt;
    }
}

void waiting_time() {
    for (int i = 0; i < 5; i++)
        p[i].wt = p[i].st - p[i].at;
}

void turnaround_time() {
    for (int i = 0; i < 5; i++) {
        p[i].tat = p[i].ct - p[i].at;
    }
}

int main() {
    FILE *fp;
    char ch;

    int avgwt = 0, avgtat = 0;

    fp = fopen("process_info.txt", "w");

    if (fp == NULL) {
        printf("\nError Opening File\n");
        exit(0);
    } else {
        fprintf(fp, "\nPID\tPNAME\tBT\tAT\tST\tWT\tTAT\tCT\n");
        printf("The file has been opened successfully\n");

        for (int i = 0; i < 5; i++) {
            printf("\nEnter PID, PNAME, BT, AT : ");
            scanf("%d %s %d %d", &p[i].pid, p[i].pname, &p[i].bt, &p[i].at);
        }

        start_time();
        completion_time();
        waiting_time();
        turnaround_time();

        for (int i = 0; i < 5; i++) {
            fprintf(fp, "%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].pname, p[i].bt, p[i].at, p[i].st,
                    p[i].wt, p[i].tat, p[i].ct);
            avgwt += p[i].wt;
            avgtat += p[i].tat;
        }

        fprintf(fp, "\n\nAverage waiting Time is  : %.2f", (float)avgwt / 5.0);
        fprintf(fp, "\nAverage turnaround Time is  : %.2f", (float)avgtat / 5.0);

        fclose(fp);

        fp = fopen("process_info.txt", "r");

        printf("\n\nThe file is opened successfully\n");

        while ((ch = fgetc(fp)) != EOF) {
            printf("%c", ch);
        }

        printf("\n------------- Gantt chart--------------\n");
        printf("\n P1-------P2-------P3-------P4-------P5\n");
        printf("Waiting Time:\t");
        for (int i = 0; i < 5; i++) {
            printf("%d\t", p[i].wt);
        }
        printf("\nCompletion Time:\t");
        for (int i = 0; i < 5; i++) {
            printf("%d\t", p[i].ct);
        }

        printf("\n");
    }

    return 0;
}
