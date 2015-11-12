//Yuxuan Huang
//csci315 Lab8

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "allocator.h"

int main(int argc, char *argv[]){
    int algo;
    unsigned int seed;
    int int_req;
    
    if (argc < 4){
        printf("usage: frag-eval [algorithm] [seed] [int requests]\n");
        return -1;
    }
    
    algo = atoi(argv[1]);
    seed = atoi(argv[2]);
    int_req = atoi(argv[3]);
    
    if (algo!=0 && algo!=1 && algo!=2){
        printf("Bad algorithm number:0 (means first-fit), 1 (means best-fit), 2 (means worst-fit)\n");
        return -1;
    }
    
    
    //void *ptr[5];
    printf("initiate with size 100000 bits\n");
    allocator_init(10000);
    //print_list();
    
    srandom(seed);
    
    int r = 0;
    int s;
    void *p = NULL;
    if(algo==0){
        srandom(seed);
        while(r<int_req){
            s = (rand()%900)+100;
            printf("%d\n",s);
            p = allocate_first(s);
            deallocate(p);
            r++;
        }
        average_frag();
        //print_list();
        return 0;
    }
    else if(algo==1){
        srandom(seed);
        while(r<int_req){
            s = (rand()%900)+100;
            printf("%d\n",s);
            p = allocate_best(s);
            //print_list();
            deallocate(p);
            r++;
        }
        average_frag();
        //print_list();
        return 0;
    }
    else{
        srandom(seed);
        while(r<int_req){
            s = (rand()%900)+100;
            printf("%d\n",s);
            p = allocate_worst(s);
            deallocate(p);
            r++;
        }
        average_frag();
        //print_list();
        return 0;
    }

}