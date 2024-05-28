#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[], int at[]) {
    int service_time[n];
    service_time[0] = at[0];
    wt[0] = 0;

    for (int i = 1; i < n; i++) {
        service_time[i] = service_time[i-1] + bt[i-1];
        wt[i] = service_time[i] - at[i];

        if (wt[i] < 0) {
            wt[i] = 0;
        }
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void createGanttChart(int processes[], int n, int bt[], int wt[], int at[]) {
    int currentTime = 0;
    printf("Gantt Chart:\n");
    for (int i = 0; i < n; i++) {
        while (currentTime < at[i]) {
            printf("--");
            currentTime++;
        }
        printf("P%d ", processes[i]);
        currentTime += bt[i];
    }
    printf("\n");
}

void findavgTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Sort processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (at[j] > at[j + 1]) {
                int temp = at[j];
                at[j] = at[j + 1];
                at[j + 1] = temp;

                temp = bt[j];
                bt[j] = bt[j + 1];
                bt[j + 1] = temp;

                temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    findWaitingTime(processes, n, bt, wt, at);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes Burst time Waiting time Turn around time\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf(" %d \t\t%d \t\t%d \t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    float avg_wt = (float)total_wt / (float)n;
    float avg_tat = (float)total_tat / (float)n;
    printf("Average waiting time = %f\n", avg_wt);
    printf("Average turn around time = %f\n", avg_tat);

    createGanttChart(processes, n, bt, wt, at);
}

int main() {
    int n;
    printf("Enter the number of processes:\n");
    scanf("%d", &n);

    int processes[n], burst_time[n], arrival_time[n];

    printf("Enter the burst time and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &burst_time[i]);
        printf("Enter arrival time for process %d: ", i + 1);
        scanf("%d", &arrival_time[i]);
        processes[i] = i + 1;
    }

    findavgTime(processes, n, burst_time, arrival_time);

    return 0;
}
