#include <stdio.h>

struct Process { int id;
int arrival_time; int burst_time;
int remaining_time; int turnaround_time; int completion_time; int start_time;
int last_execution_time; // This tracks when the process was last executed
};

int main() {
int num_processes, quantum;
printf("Enter the number of processes: "); scanf("%d", &num_processes);
printf("Enter the time quantum: "); scanf("%d", &quantum);

struct Process processes[num_processes];
printf("\nEnter arrival time and burst time for each process:\n"); for (int i = 0; i < num_processes; i++) {
printf("Process %d:\n", i + 1); printf("Arrival time: ");
scanf("%d", &processes[i].arrival_time); printf("Burst time: ");
scanf("%d", &processes[i].burst_time);
 
processes[i].id = i + 1;
processes[i].remaining_time = processes[i].burst_time;
processes[i].last_execution_time = processes[i].arrival_time; // Initialize to arrival time processes[i].start_time = -1; // Not started yet
}

int current_time = 0, processes_done = 0; while (processes_done < num_processes) {
int all_idle = 1; // To check if all processes are idle in a cycle

for (int i = 0; i < num_processes; i++) {
if (processes[i].remaining_time > 0 && processes[i].arrival_time <= current_time) { all_idle = 0; // There's at least one process available to run

if (processes[i].start_time == -1) { // Set start time if first run processes[i].start_time = current_time;
}

if (processes[i].remaining_time > quantum) { current_time += quantum;
processes[i].remaining_time -= quantum;
processes[i].last_execution_time = current_time;
} else {
current_time += processes[i].remaining_time; processes[i].completion_time = current_time;
processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
processes[i].remaining_time = 0; processes_done++;
}
}
}

if (all_idle) { // If all processes are waiting and none could execute, increment time current_time++;
}
}

printf("\nProcess\tArrival Time\tBurst Time\tStart Time\tCompletion Time\tTurnaround Time\n");
for (int i = 0; i < num_processes; i++) {
printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", processes[i].id, processes[i].arrival_time,
 
processes[i].burst_time, processes[i].start_time,
processes[i].completion_time, processes[i].turnaround_time);
}
return 0;
}
