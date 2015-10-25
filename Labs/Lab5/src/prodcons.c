/*
 * Copyright (c) 2013 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author: L. Felipe Perrone (perrone@bucknell.edu)
 */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h> 
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>

#include "circular-list.h" 

/* SCALE_FACTOR is a constant for you to experiment with:
 * if you choose a very large SCALE_FACTOR, your threads
 * might spend a long time sleeping. If you choose it to be
 * too small, your threads will not sleep at all. Note
 * that in the producer and consumer functions, the sleep
 * time is computed as the INTEGER DIVISION below:
 *
 *  usleep(SCALE_FACTOR * rand_r(&seed) / RAND_MAX
 *
 *  where RAND_MAX is the largest random numver returned
 *  by rand_r. If the numerator is smaller than RAND_MAX,
 *  the quotient of the integer division is ZERO!
 */
#define SCALE_FACTOR 1000

// global variables -----------------------

struct circular_list mylist;
pthread_mutex_t the_mutex = PTHREAD_MUTEX_INITIALIZER;
sem_t empty;
sem_t full;


// end of global variables ----------------

void *producer (void *param) {
    item i;
    unsigned int seed = *((unsigned int*)param);

    while (true) {
        //pthread_mutex_lock(&the_mutex);
    // sleep for random period of time
        long double d=(SCALE_FACTOR * rand_r(&seed) / RAND_MAX);
        //below is the test for problem 2
        //printf("producer sleep:%lf\n",d);
        usleep(d);
    
    // generate a random number
        i = (item) (((double) rand_r(&seed)) / RAND_MAX);

        sem_wait(&empty);
        if (circular_list_insert(&mylist, i) == -1) {
            printf("PRODUCER: error condition\n");
        } else {
            printf("PRODUCER: produced value %lf\n", i);
        }
        sem_post(&full);
        //pthread_mutex_unlock(&the_mutex);
    }
    //pthread_exit(0);
}

void *consumer (void *param) {
    item i;
    unsigned int seed = *((unsigned int*)param);

    while (true) {
        //pthread_mutex_lock(&the_mutex);
        // sleep for random period of time
        long double d=(SCALE_FACTOR * rand_r(&seed) / RAND_MAX);
        //below is the test for problem 2
        //printf("consumer sleep:%lf\n",d);
        usleep(d);

        sem_wait(&full);
        if (circular_list_remove(&mylist, &i) == -1) {
            printf("CONSUMER: error condition\n");
        } else {
            printf("CONSUMER: consumed value %lf\n", i);
        }
        sem_post(&empty);
        //pthread_mutex_unlock(&the_mutex);
    }
    //pthread_exit(0);
}

int main (int argc, char *argv[]) {
    int num_prod;
    int num_cons;
    int sleep_time;
    int i,j;
    

  // get command line arguments
    if (argc < 4){
        printf("usage: %s [num_prod][num_cons][sleep_time],incorrect input\n",argv[0]);
        exit(-1);
    }
    
    else if (atoi(argv[1])==0) {
        printf("bad producer number\n");
        exit(-1);
    }
  
    else if (atoi(argv[2])==0){
        printf("bad consumer number\n");
        exit(-1);
    }
    
    else if (atoi(argv[3])==0){
        printf("bad sleep time number\n");
        exit(-1);
    }
    
    else {
        num_prod = atoi(argv[1]);
        num_cons = atoi(argv[2]);
        sleep_time = atoi(argv[3]);
    
        pthread_t prod[num_prod];
        pthread_t cons[num_cons];
    
  // if error in command line argument usage, terminate with helpful message
  
  // initialize buffer
        circular_list_create(&mylist, 20);
        sem_init(&empty,0,20);
        sem_init(&full,0,0);
  
  // create producer thread(s)
        for (i=0;i<num_prod;i++){
            int *pid1 = malloc(sizeof(int));
            *pid1 = i;
            pthread_create(&prod[i],NULL,producer,pid1);
    }
  
  // create consumer thread(s)
        for (j=0;j<num_cons;j++){
            int *pid2 = malloc(sizeof(int));
            *pid2 = j;
            pthread_create(&cons[j],NULL,consumer,pid2);
    }
        /*
        for (i=0;i<num_prod;i++){
            pthread_join(prod[i],NULL);
    }
    
        for (j=0;j<num_cons;j++){
            pthread_join(cons[i],NULL);
    }
    */
  // sleep to give time for threads to run
        usleep(1000000*sleep_time);
  
  // exit
        return (0);
    }
    return 0;
}
