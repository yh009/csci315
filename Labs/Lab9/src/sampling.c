//Yuxuan Huang
//Lab9

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "allocator.h"

int main(){
    unsigned int seed = time(NULL);
    int i;
    void *p = NULL;
    
    printf("initiate with size 100000 bits\n");
    allocator_init(10000);
    srandom(seed);
    printf("samples for first-fit start!!\n");
    for(i=0;i<10;i++){
        int r = 0;
        int s;
        //srandom(seed);
        while(r<100){
            s = (rand()%900)+100;
            //printf("%d\n",s);
            p = allocate_first(s);
            deallocate(p);
            r++;
        }
        //seed=time(NULL);
        average_frag();
    }
    printf("samples for first-fit END!!\n\n");
    
    allocator_init(10000);

    printf("samples for best-fit start!!\n");
    for(i=0;i<10;i++){
        int r = 0;
        int s;
        //srandom(seed);
        while(r<100){
            s = (rand()%900)+100;
            //printf("%d\n",s);
            p = allocate_best(s);
            deallocate(p);
            r++;
        }
        //seed=time(NULL);
        average_frag();
    }
    printf("samples for best-fit END!!\n\n");
    
    allocator_init(10000);

    printf("samples for worst-fit start!!\n");
    for(i=0;i<10;i++){
        int r = 0;
        int s;
        //srandom(seed);
        while(r<100){
            s = (rand()%900)+100;
            //printf("%d\n",s);
            p = allocate_worst(s);
            deallocate(p);
            r++;
        }
        //seed=time(NULL);
        average_frag();
    }
    printf("samples for worst-fit END!!\n\n");
    
    return 0;
}