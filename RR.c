#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Macros
#define SIZE 100

// Global Variables
// struct proc
// {
//     int pid;
//     int arrival_time;
//     int burst_time;
//     int completion_time;
//     int remaining_time;
//     int turnaround_time;
//     int waiting_time;

// } process[SIZE], temp[100];

int pid[SIZE];
int arrival_time[SIZE];
int burst_time[SIZE];
int completion_time[SIZE];
int remaining_time[SIZE];
int turnaround_time[SIZE];
int waiting_time[SIZE];

int num_process;
int counter = 0;
int i;
int proc_count = 0;
int sum = 0;
int time_quantum = 0;
int total_waiting_time = 0;
int total_turnaround_time = 0;
float average_waiting_time, average_turnaround_time;

// Function Definitions
void get_process_data(void)
{
    // Code
    printf("\nEnter Number Of Processes = ");
    scanf("%d", &num_process);

    counter = num_process;

    printf("\nProcess Data : \n");
    for (int i = 0; i < num_process; i++)
    {
        printf("\nPID = ");
        scanf("%d", &pid[i]);

        printf("Arrival Time For Process P%d = ", pid[i]);
        scanf("%d", &arrival_time[i]);

        printf("Burst Time For Process P%d = ", pid[i]);
        scanf("%d", &burst_time[i]);

        remaining_time[i] = burst_time[i];
    }

    printf("\nEnter Time Quantum = ");
    scanf("%d", &time_quantum);
}

void schedule_process(void)
{
    // Sort
    for (int i = 0; i < num_process; i++)
    {
        for (int j = 0; j < num_process; j++)
        {
            if (arrival_time[j] > arrival_time[i])
            {
                int temp = arrival_time[i];
                arrival_time[i] = arrival_time[j];
                arrival_time[j] = temp;

                temp = burst_time[i];
                burst_time[i] = burst_time[j];
                burst_time[j] = temp;

                temp = pid[i];
                pid[i] = pid[j];
                pid[j] = temp;
            }

            else if (arrival_time[j] == arrival_time[i])
            {
                if (pid[j] > pid[i])
                {
                    int temp = arrival_time[i];
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
    }

    printf("\nGantt Chart: \n\n");
    for (sum = 0, i = 0; counter != 0;)
    {
        if (remaining_time[i] <= time_quantum && remaining_time[i] > 0)
        {
            sum = sum + remaining_time[i];
            printf("[P%d]  ", pid[i]);
            remaining_time[i] = 0;
            proc_count = 1;    
        }
        else if (remaining_time[i] > 0)
        {
            remaining_time[i] = remaining_time[i] - time_quantum;
            sum = sum + time_quantum;
            printf("[P%d]  ", pid[i]);     
        }

        if (remaining_time[i] == 0 && proc_count == 1)
        {
            counter--;

            pid[i] = i + 1;
            completion_time[i] = sum;
            turnaround_time[i] = sum - arrival_time[i];
            waiting_time[i] = sum - arrival_time[i] - burst_time[i];

            total_waiting_time = total_waiting_time + sum - arrival_time[i] - burst_time[i];
            total_turnaround_time = total_turnaround_time + sum - arrival_time[i];
            proc_count = 0;
        }

        if (i == num_process - 1)
            i = 0;
        else if (arrival_time[i + 1] <= sum)
            i++;
        else 
            i = 0;
    }

    average_waiting_time = total_waiting_time * 1.0 / num_process;
    average_turnaround_time = total_turnaround_time * 1.0 / num_process;
}

void show_process_data(void)
{
    printf("\n\nOutput:\n");
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    printf("---------------------------------------------------------------\n");
    for (int i = 0; i < num_process; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], arrival_time[i], burst_time[i], completion_time[i], turnaround_time[i], waiting_time[i]);
    }
    printf("---------------------------------------------------------------\n");
    printf("\nAverage Turnaround Time = %.2f", average_turnaround_time);
    printf("\nAverage Waiting Time = %.2f\n", average_waiting_time);
}


int main(void)
{
    get_process_data();
    schedule_process();
    show_process_data();
    
    return 0;
}
