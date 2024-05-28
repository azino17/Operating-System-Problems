#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

void *Philosopher(void *arg);
void printstatus();

sem_t chop[5];
sem_t mutex;
char status[6] = {'-','-','-','-','-','-'};

int main()
{
    pthread_t phil[5];
    long int i,j;

    for(i=0;i<5;i++)
    {
        sem_init(&chop[i],0,1); // 0 means not shared with others process .... and last 1 means chopstick is free now..
    }
    sem_init(&mutex,0,1);
    
    printf("\n");

    //printing heading of table
    for(i=0;i<5;i++)
    {
        printf(" P[%ld]",i);
    }

    for(i=0;i<5;i++)
    {
        pthread_create(&phil[i],NULL,Philosopher,(void*)i);
    }

    for(j=0;j<5;j++)
    {
        pthread_join(phil[j],NULL);
    }
}

void *Philosopher(void *arg)
{
  long int num = (long int)arg;
   
   // philosopher is hungry

   status[num] = 'H';
   printstatus();

   //Acquire chopstick[left and right]
   sem_wait(&mutex);
   sem_wait(&chop[num]);
   sleep(1);
   sem_wait(&chop[(num+1)%5]);
   sem_post(&mutex);
   status[num] = 'E';
   printstatus();
   sleep(1);  // philosopher eating hence we give him 
   
   //release chostick

   sem_post(&chop[(num+1)%5]);
   sem_post(&chop[num]);

   //philosopher is thinking
   status[num] = 'T';
   printstatus();

   pthread_exit(NULL);
}

void printstatus()
{
    printf("\n");

    for(int i=0;i<5;i++)
    {
        printf("    %c",status[i]);
    }
}

