//Yuxuan Huang
//csci315 pre-lab7
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;


void napping(int t){
    unsigned int seed = t;
    int wait_sec = (rand_r(&seed)%t)+1;
    long int wait_micro = wait_sec*1000000L;
    printf("nap for %d seconds\n",wait_sec);
    if(usleep(wait_micro)==-1){
        perror("usleep");
    }
}

struct thread_args {
    int tid;
};

void *Philosopher(void *id){
    int pid = *((int*)id);
    int special = pid+1;
    
    printf("Pilosopher %d is thinking.\n",pid);
    napping(special);
    printf("Pilosopher %d is hungry.\n",pid);
    pthread_mutex_lock(&lock);
    printf("Pilosopher %d is starting to eat.\n",pid);
    napping(special);
    printf("Pilosopher %d is done eating.\n",pid);
    pthread_mutex_unlock(&lock);
    return 0;
}

int main(){
    pthread_t pilosophers[5];
    int i;
    
    for (i=0;i<5;i++){
        int *pid = malloc(sizeof(int));
        *pid = i;
        pthread_create(&pilosophers[i],NULL,Philosopher,pid);
    }
    usleep(1000000*20);
    return 0;
}