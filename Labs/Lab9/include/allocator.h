//Yuxuan Huang
//Lab8

#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int allocator_init(size_t size);

void *allocate_first(size_t size);

void *allocate_best(size_t size);

void *allocate_worst(size_t size);

int deallocate(void *ptr);

void print_list();

double average_frag();


#endif