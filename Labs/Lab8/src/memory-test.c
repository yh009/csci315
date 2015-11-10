//Yuxuan Huang
//csci315 Lab8

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "allocator.h"

int main(){
    void *ptr[5];
    printf("initiate with size 300\n");
    allocator_init(300);
    print_list();
    
    printf("testing first-fit\n");
    printf("allocate 1st node: size 10\n");
    ptr[0]=allocate_first(10);
    print_list();
    
    printf("allocate 2nd node: size 20\n");
    ptr[1]=allocate_first(20);
    print_list();
    
    printf("allocate 3nd node: size 30\n");
    ptr[2]=allocate_first(30);
    print_list();
    
    printf("deallocate 3nd node\n");
    deallocate(ptr[2]);
    print_list();
    
    printf("allocate 3nd node: size 40\n");
    ptr[3]=allocate_first(40);
    print_list();
    
    printf("deallocate 2nd node\n");
    deallocate(ptr[2]);
    print_list();
    
    printf("allocate 3nd node: size 50\n");
    ptr[4]=allocate_first(50);
    print_list();
    
    return 0;
}