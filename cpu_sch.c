#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct Process
{
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
    int response_time;
} Process;

void fcfs(Process processes[], int n)
{
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        current_time += processes[i].burst_time;
        processes[i].waiting_time = current_time - processes[i].arrival_time - processes[i].burst_time;
        processes[i].turnaround_time = current_time - processes[i].arrival_time;
        processes[i].response_time = 0;
    }
}

void sjf(Process processes[], int n)
{
    // Shortest Job First (SJF) scheduling is non-preemptive.
    // You can implement it using sorting before calling the fcfs function.
    // Sort processes based on burst time.
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (processes[j].burst_time > processes[j + 1].burst_time)
            {
                // Swap processes[j] and processes[j+1]
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
    // Call the FCFS function to calculate waiting and turnaround times.
    fcfs(processes, n);
}

void srtf(Process processes[], int n)
{
    // Shortest Remaining Time First (SRTF) scheduling is preemptive.
    int current_time = 0;
    int remaining[n];
    memset(remaining, 0, sizeof(remaining));

    while (1)
    {
        int shortest_remaining_time = INT_MAX;
        int shortest_remaining_index = -1;
        int flag = 0;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].arrival_time <= current_time && remaining[i] < shortest_remaining_time && remaining[i] > 0)
            {
                shortest_remaining_time = remaining[i];
                shortest_remaining_index = i;
                flag = 1;
            }
        }
        if (!flag)
        {
            // If no process is ready to execute, move to the next time unit.
            current_time++;
        }
        else
        {
            // Execute the process with the shortest remaining time for one time unit.
            int index = shortest_remaining_index;
            current_time++;
            processes[index].burst_time--;

            if (processes[index].burst_time == 0)
            {
                // Process is completed.
                processes[index].turnaround_time = current_time - processes[index].arrival_time;
                processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
                processes[index].response_time = processes[index].waiting_time;
            }
        }

        // Check if all processes are completed.
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (remaining[i] > 0)
            {
                done = 0;
                break;
            }
        }

        if (done)
            break;
    }
}

void rr(Process processes[], int n, int time_quantum)
{
    int current_time = 0;
    Process remaining[n]; // Declare remaining as an array of Process structures

    // Initialize the remaining array by copying from the processes array
    for (int i = 0; i < n; i++)
    {
        remaining[i] = processes[i];
    }

    while (1)
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            if (remaining[i].burst_time > 0)
            {
                done = 0;
                if (remaining[i].burst_time > time_quantum)
                {
                    current_time += time_quantum;
                    remaining[i].burst_time -= time_quantum;
                }
                else
                {
                    current_time += remaining[i].burst_time;
                    remaining[i].waiting_time = current_time - remaining[i].arrival_time - remaining[i].burst_time;
                    remaining[i].turnaround_time = current_time - remaining[i].arrival_time;
                    remaining[i].response_time = remaining[i].waiting_time;
                    remaining[i].burst_time = 0;
                }
            }
        }

        if (done)
            break;
    }
}
void non_preemptive_priority(Process processes[], int n)
{
    int current_time = 0;
    int completed[n];
    memset(completed, 0, sizeof(completed));

    while (1)
    {
        int highest_priority = INT_MAX;
        int highest_priority_index = -1;

        int flag = 0;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority)
            {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
                flag = 1;
            }
        }

        if (!flag)
        {
            // If no process is ready to execute, move to the next time unit.
            current_time++;
        }
        else
        {
            // Execute the process with the highest priority.
            int index = highest_priority_index;
            current_time += processes[index].burst_time;
            processes[index].waiting_time = current_time - processes[index].arrival_time - processes[index].burst_time;
            processes[index].turnaround_time = current_time - processes[index].arrival_time;
            processes[index].response_time = processes[index].waiting_time;
            completed[index] = 1;
        }

        // Check if all processes are completed.
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                done = 0;
                break;
            }
        }

        if (done)
            break;
    }
}

void preemptive_priority(Process processes[], int n)
{
    int current_time = 0;
    int completed[n];
    memset(completed, 0, sizeof(completed));

    while (1)
    {
        int highest_priority = INT_MAX;
        int highest_priority_index = -1;

        int flag = 0;

        for (int i = 0; i < n; i++)
        {
            if (!completed[i] && processes[i].arrival_time <= current_time && processes[i].priority < highest_priority)
            {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
                flag = 1;
            }
        }

        if (!flag)
        {
            // If no process is ready to execute, move to the next time unit.
            current_time++;
        }
        else
        {
            // Execute the process with the highest priority for one time unit.
            int index = highest_priority_index;
            current_time++;
            processes[index].burst_time--;

            if (processes[index].burst_time == 0)
            {
                // Process is completed.
                processes[index].turnaround_time = current_time - processes[index].arrival_time;
                processes[index].waiting_time = processes[index].turnaround_time - processes[index].burst_time;
                processes[index].response_time = processes[index].waiting_time;
                completed[index] = 1;
            }
        }

        // Check if all processes are completed.
        int done = 1;
        for (int i = 0; i < n; i++)
        {
            if (!completed[i])
            {
                done = 0;
                break;
            }
        }

        if (done)
            break;
    }
}

int main()
{
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    for (int i = 0; i < n; i++)
    {
        printf("Enter details for Process %d:\n", i + 1);
        processes[i].pid = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].response_time = 0;
    }

    fcfs(processes, n);
    sjf(processes, n);
    srtf(processes, n);
    rr(processes, n, 2);
    non_preemptive_priority(processes, n);
    preemptive_priority(processes, n);

    printf("Process\tArrival Time\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\tResponse Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time, processes[i].response_time);
    }

    return 0;
}