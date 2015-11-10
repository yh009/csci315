//Yuxuan Huang
//Lab8 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "dlist.h"
#include "dnode.h"
#include "allocator.h"


struct dlist *free_list;
struct dlist *allocated_list;

int allocator_init(size_t size){
    void *ptr = malloc(size);
    struct dnode *init = dnode_create();
    
    free_list = dlist_create();
    allocated_list = dlist_create();

    dlist_add_front(free_list,ptr,size);
    
    if(free_list==NULL||allocated_list==NULL||init==NULL||ptr==NULL){
        return -1;
    }
    return 0;
}



void *allocate_first(size_t size){
    struct dnode *free = free_list->front;
    void *ptr;
    
    while(free != NULL){
        if (free->size>=size){
            ptr = free->data;
            dlist_add_back(allocated_list,ptr,size);
            dnode_setdata(free,free->data + size);
            dnode_setsize(free,free->size - size);
            return ptr;
        }
        free = free->next;
    }
    return NULL;

}

void *allocate_best(size_t size){
    struct dnode *free = free_list->front;
    struct dnode *best = free_list->front;
    void *ptr;
    
    while(free != NULL){
        if(free->size >= size && free->size < best->size){
            best = free;
        }
        free = free->next;
    }
    if(sizeof(best)>size){
        ptr = best->data;
        dlist_add_back(allocated_list,ptr,size);
        dnode_setdata(best,best->data + size);
        dnode_setsize(best,best->size - size);
        return ptr;
    }
    else{
        return NULL;
    }
}

void *allocate_worst(size_t size){
    struct dnode *free = free_list->front;
    struct dnode *worst = free_list->front;
    void *ptr;
    
    while(free != NULL){
        if(free->size >= size && free->size > worst->size){
            worst = free;
        }
        free = free->next;
    }
    if(worst->size >= size){
        ptr = worst->data;
        dlist_add_back(allocated_list,ptr,size);
        dnode_setdata(worst,worst->data + size);
        dnode_setsize(worst,worst->size - size);
        return ptr;
    }
    else{
        return NULL;
    }
}

int deallocate(void *ptr){
    struct dnode *n = allocated_list->front;
    void *the_ptr;
    
    while((n != NULL) && (n->data != ptr)){
        n = n->next;
    }
    
    if(n == NULL){
        return -1;
    }
    
    else{
        the_ptr = n->data;
        size_t size = n->size;
        struct dnode *new = dnode_create();
        new->data = the_ptr;
        new->size = size;
        
        if(free_list->counter == 0){
            free_list->front = free_list->back = new;
            free_list->counter++;
        }
        else{struct dnode *n = free_list->front;
            if(the_ptr < n->data){
                dlist_add_front(free_list,the_ptr,size);
            }
            else{
                while(n != NULL){
                    if(n==free_list->back){
                        dlist_add_back(free_list,the_ptr,size);
                        break;
                    }
                    else if(the_ptr < n->next->data){
                        new->prev = n;
                        new->next = n->next;
                        n->next = new;
                        new->next->prev = new;
                        (free_list->counter)++;
                        break;
                    }
                    else{
                        n=n->next;
                    }
                }
            }
        }

        dlist_find_remove(allocated_list,the_ptr);
        return 0;
    }
}


void print_list(){
    int i = 0;
    struct dnode *n = free_list->front;
    printf("free_list: \n");
    
    while(n != NULL){
        printf("Node#:%d; Size:%zd\n",i,n->size);
        n = n->next;
        i++;
    }
    i=0;
    struct dnode *m = allocated_list->front;
    printf("\nallocated_list: \n");
    
    while(m != NULL){
        printf("Node#:%d; Size:%zd\n",i,m->size);
        m = m->next;
        i++;
    }
    printf("End\n");
}

