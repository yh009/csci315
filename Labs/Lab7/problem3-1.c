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


void napping(int t,long long pid){
    unsigned int seed = (unsigned int)pid+1;
    int value = rand_r(&seed);
    int wait_microsec = value%(t*1000000);
    printf("nap for %d microseconds\n",wait_microsec);
    usleep(wait_microsec);
}




void *Philosopher(void *id){
    long long pid = *((long long*)id);
    long long special = pid;
    while(1){
        printf("Pilosopher %lld is thinking.\n",pid);
        fflush(stdout);
        //napping(3,special);
        printf("Pilosopher %lld is hungry.\n",pid);
        fflush(stdout);
        if(pid%2==0){
            pthread_mutex_lock(&chop_lock[pid]);
            printf("Pilosopher %lld picked up chopstick on the left.\n",pid);
            fflush(stdout);
            napping(1,special);
            special=special*3+5;
            pthread_mutex_lock(&chop_lock[(pid+1)%5]);
            printf("Pilosopher %lld picked up chopstick on the right.\n",pid);
            fflush(stdout);
            printf("Pilosopher %lld is starting to eat.\n",pid);
            fflush(stdout);
            printf("Pilosopher %lld is done eating.\n",pid);
            fflush(stdout);
            pthread_mutex_unlock(&chop_lock[pid]);
            printf("Pilosopher %lld put back chopstick on the left.\n",pid);
            fflush(stdout);
            pthread_mutex_unlock(&chop_lock[(pid+1)%5]);
            printf("Pilosopher %lld put back chopstick on the right.\n",pid);
            fflush(stdout);
        }
        else{
            pthread_mutex_lock(&chop_lock[(pid+1)%5]);
            printf("Pilosopher %lld picked up chopstick on the right.\n",pid);
            fflush(stdout);
            napping(1,special);
            special=special*2+7;
            pthread_mutex_lock(&chop_lock[pid]);
            printf("Pilosopher %lld picked up chopstick on the left.\n",pid);
            fflush(stdout);
            printf("Pilosopher %lld is starting to eat.\n",pid);
            fflush(stdout);
            printf("Pilosopher %lld is done eating.\n",pid);
            fflush(stdout);
            pthread_mutex_unlock(&chop_lock[(pid+1)%5]);
            printf("Pilosopher %lld put back chopstick on the right.\n",pid);
            fflush(stdout);
            pthread_mutex_unlock(&chop_lock[pid]);
            printf("Pilosopher %lld put back chopstick on the left.\n",pid);
            fflush(stdout);
        }
    }
    return 0;
}
    
int main(){
    pthread_t pilosophers[5];
    int i,j;
    for (j=0;j<5;j++){
        pthread_mutex_init(&chop_lock[j],NULL);
    }
    for (i=0;i<5;i++){
        long long *pid = malloc(sizeof(long long));
        *pid = i;
        pthread_create(&pilosophers[i],NULL,Philosopher,pid);
    }
    for (i = 0;i<5;i++){
        pthread_join(pilosophers[i],NULL);
    }
}