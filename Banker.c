#include <stdio.h>

int num_process, num_resources, instance;
int k = 0, count = 0, temp = 0;

int main(void)
{
    printf("\nEnter Number Of Processes = ");
    scanf("%d", &num_process);

    printf("\nEnter Number Of Resources = ");
    scanf("%d", &num_resources);

    int available[num_resources], max[num_process][num_resources], allocated[num_process][num_resources], need[num_process][num_resources], completed[num_process];

    for (int i = 0; i< num_process; i++)
        completed[i] = 0;

    printf("\nEnter Number Of AVAILABLE Instances For Each Resource : \n");
    for (int i = 0; i < num_resources; i++)
    {
        printf("Resources[%d] : ", i);
        scanf("%d", &instance);
        available[i] = instance;
    }

    printf("\n------------------------------------------------------------------------------\n");
    printf("\nEnter MAXIMUM Instances For A Process & Its Resource :\n");
    for (int i = 0; i < num_process; i++)
    {
        printf("\nFor Process[%d] \n", i);
        for(int j = 0; j < num_resources; j++)
        {
            printf("Resource[%d] : ", j);
            scanf("%d", &instance);
            max[i][j] = instance;
        }
    }

    printf("\n------------------------------------------------------------------------------\n");
    printf("\nEnter Instances ALLOCATED For A Process & Its Resource :\n");
    for (int i = 0; i < num_process; i++)
    {
        printf("\nFor Process[%d] \n", i);
        for(int j = 0; j < num_resources; j++)
        {
            printf("Resource[%d] : ", i);
            scanf("%d", &instance);
            allocated[i][j] = instance;
            need[i][j] = max[i][j] - allocated[i][j];
        }
    }

    printf("\n------------------------------------------------------------------------------\n");
    printf("\nSafe Sequence is : ");
    while(count != num_process)
    {
        count = temp;

        for(int i = 0; i < num_process; i++)
        {
            for(int j = 0; j < num_resources; j++)
            {
                if (need[i][j] <= available[j])
                    k++;
            }

            if (k == num_resources && completed[i] == 0 )
            {
                printf(" > P[%d] ", i);
                completed[i] = 1;
                for(int j = 0; j < num_resources; j++)
                    available[j] = available[j] + allocated[i][j];
                count++;
            }

            k=0;
        }

        if (count == temp)
            break;
    }

    for(int i = 0; i < num_process; i++)
    {
        if(completed[i] != 1)
        printf("\n\n P[%d] not able to allocate", i);
    }

    printf("\n");

    return 0;
}

