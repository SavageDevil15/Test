#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

#define NUM_PHILOSOPHERS 5
#define NUM_CHOPSTICKS 5

sem_t room;
sem_t chopsticks[5];

void *eat(int current_philosoper)
{
    printf("Philosopher %d Is Eating\n", current_philosoper);
}

void* philosopher(void *num)
{
    int i_philosopher = *(int*)num;

    sem_wait(&room);

    printf("Philosopher %d Has Entered The Dining Room\n", i_philosopher);

    sem_wait(&chopsticks[i_philosopher]);
    sem_wait(&chopsticks[(i_philosopher + 1) % NUM_CHOPSTICKS]);

    eat(i_philosopher);

    sleep(2);

    printf("Philosopher %d Has Finished Eating\n", i_philosopher);

    sem_post(&chopsticks[(i_philosopher + 1) % NUM_CHOPSTICKS]);
    sem_post(&chopsticks[i_philosopher]);
    sem_post(&room);
}

int main(void)
{
    int arr[NUM_PHILOSOPHERS];
    pthread_t philosopher_threads[NUM_PHILOSOPHERS];
    
    sem_init(&room, 0, 4);
   
    for (int i = 0; i < NUM_CHOPSTICKS; i++)
        sem_init(&chopsticks[i], 0, 1);
    
    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
    {
        arr[i] = i;
        pthread_create(&philosopher_threads[i], NULL, philosopher, (void*)&arr[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++)
        pthread_join(philosopher_threads[i], NULL);

    return 0;
    
}
