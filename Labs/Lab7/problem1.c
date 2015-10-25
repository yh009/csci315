//Yuxuan Huang
//csci315 Lab7
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>

pthread_mutex_t chop_lock[5];

/*
void napping(int t,int pid){
    unsigned int seed = pid;
    int value = rand_r(&seed);
    int wait_microsec = value%(t*1000);
    //printf("nap for %d microseconds\n",wait_microsec);
    usleep(wait_microsec);
}
*/




void *Philosopher(void *id){
    int pid = *((int*)id);
    //int special = pid;
    while(1){
      printf("Pilosopher %d is thinking.\n",pid);
      fflush(stdout);
      //napping(1,special);
      printf("Pilosopher %d is hungry.\n",pid);
      fflush(stdout);
      pthread_mutex_lock(&chop_lock[pid]);
      printf("Pilosopher %d picked up chopstick on the left.\n",pid);
      fflush(stdout);
      pthread_mutex_lock(&chop_lock[(pid+1)%5]);
      printf("Pilosopher %d picked up chopstick on the right.\n",pid);
      fflush(stdout);
      printf("Pilosopher %d is starting to eat.\n",pid);
      fflush(stdout);
      //napping(1,special);
      printf("Pilosopher %d is done eating.\n",pid);
      fflush(stdout);
      pthread_mutex_unlock(&chop_lock[pid]);
      printf("Pilosopher %d put back chopstick on the left.\n",pid);
      fflush(stdout);
      pthread_mutex_unlock(&chop_lock[(pid+1)%5]);
      printf("Pilosopher %d put back chopstick on the right.\n",pid);
      fflush(stdout);
    }
    return 0;
}

int main(){
    pthread_t pilosophers[5];
    int i,j;
    for (j=1;j<6;j++){
      pthread_mutex_init(&chop_lock[j],NULL);
    }
    for (i=1;i<6;i++){
        int *pid = malloc(sizeof(int));
        *pid = i;
        pthread_create(&pilosophers[i],NULL,Philosopher,pid);
    }
    usleep(1000000*2000);
    return 0;
}
