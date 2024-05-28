#include <stdio.h>

struct Process {
    int id;             
    int arrival_time;   
    int burst_time;     
    int priority;       
    int turnaround_time; 
    int completion_time; 
    int start_time;      
};

void swap(struct Process *a, struct Process *b) {
    struct Process temp = *a;
    *a = *b;
    *b = temp;
}

void sortByPriority(struct Process processes[], int num_processes) {
    for (int i = 0; i < num_processes - 1; i++) {
        for (int j = 0; j < num_processes - i - 1; j++) {
            if (processes[j].priority > processes[j + 1].priority) {
                swap(&processes[j], &processes[j + 1]);
            }
        }
    }
}

int main() {
    int num_processes;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    struct Process processes[num_processes];

    printf("\nEnter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < num_processes; i++) {
        printf("Process %d:\n", i + 1);
        printf("Arrival time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].id = i + 1;
    }

    sortByPriority(processes, num_processes);

    int current_time = 0;
    for (int i = 0; i < num_processes; i++) {
        processes[i].start_time = current_time;
        current_time += processes[i].burst_time;
        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
    }

    printf("\nProcess\tArrival Time\tBurst Time\tPriority\tStart Time\tCompletion Time\tTurnaround Time\n");
    for (int i = 0; i < num_processes; i++) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time, 
               processes[i].burst_time, processes[i].priority, processes[i].start_time,
               processes[i].completion_time, processes[i].turnaround_time);
    }

    return 0;
}
