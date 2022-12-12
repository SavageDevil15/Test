#include <stdio.h>
#include <stdlib.h>

// Macros
#define SIZE 100
#define TRUE 1
#define FALSE -1

int pid[SIZE];
int priority[SIZE];
int arrival_time[SIZE];
int burst_time[SIZE];
int completion_time[SIZE];
int turnaround_time[SIZE];
int waiting_time[SIZE];
int starting_time[SIZE];

int num_process;
int sum = 0;
float average_waiting_time, average_turnaround_time;

void get_process_data(void)
{
    printf("\nEnter Number Of Processes = ");
    scanf("%d", &num_process);

    printf("\nProcess Data : \n");
    for (int i = 0; i < num_process; i++)
    {
        printf("\nPID = ");
        scanf("%d", &pid[i]);

        printf("Arrival Time For Process P%d = ", pid[i]);
        scanf("%d", &arrival_time[i]);

        printf("Burst Time For Process P%d = ", pid[i]);
        scanf("%d", &burst_time[i]);

        printf("Priority For Process P%d = ", pid[i]);
        scanf("%d", &priority[i]);
    }
}

void schedule_process(void)
{
    // Sort
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < num_process; j++)
        {
            if (priority[i] < priority[j])
            {
                int temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }
        }
    }

    for (int i = 0; i < num_process; i++)
    {
        if (i == 0)
            starting_time[i] = arrival_time[i];
        else
            starting_time[i] = completion_time[i - 1];
        
        completion_time[i] = starting_time[i] + burst_time[i];
        turnaround_time[i] = completion_time[i] - arrival_time[i];
        waiting_time[i] = turnaround_time[i] - burst_time[i];

        average_waiting_time += waiting_time[i];
        average_turnaround_time += turnaround_time[i]; 
    }

    average_turnaround_time = average_turnaround_time / num_process;
    average_waiting_time = average_waiting_time / num_process;
}

void print_gantt_chart(void)
{
    printf("\nGantt Chart: \n\n");

    // Top Bar
    printf(" ");
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < burst_time[i]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n|");
    
    // Process ID
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < burst_time[i] - 1; j++)
            printf(" ");
        printf("P%d", pid[i]);
        for (int j = 0; j < burst_time[i] - 1; j++)
            printf(" ");
        printf("|");
    }
    printf("\n ");

    // Bottom Bar
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < burst_time[i]; j++)
            printf("--");
        printf(" ");
    }
    printf("\n");

    // Timeline
    printf("0");
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < burst_time[i]; j++)
            printf("  ");
        if (turnaround_time[i] > 9)
            printf("\b");
        printf("%d", completion_time[i]);
    }

    printf("\n");
}

void show_process_data(void)
{
    printf("\nOutput:\n");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tPriority\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < num_process; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i], priority[i]);
    }
    printf("---------------------------------------------------------------\n");
    printf("\nAverage Turnaround Time = %.2f", average_turnaround_time);
    printf("\nAverage Waiting Time = %.2f\n", average_waiting_time);

    print_gantt_chart();
}

int main(void)
{
    get_process_data();
    schedule_process();
    show_process_data();
    
    return 0;
}