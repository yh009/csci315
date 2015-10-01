//Yuxuan Huang
#include <stdlib.h>
#include <stdio.h>
#include "circular-list.h" 

int main(int argc, char* argv[]){
  struct circular_list l;
  item p;
  circular_list_create(&l,3);
  printf("list size:%i\n",l.size);
  circular_list_insert(&l,1);
  circular_list_insert(&l,2);
  circular_list_insert(&l,3);
  circular_list_insert(&l,4);
  circular_list_remove(&l,&p);
  printf("%f\n",p);
  circular_list_remove(&l,&p);
  printf("%f\n",p);
  circular_list_remove(&l,&p);
  printf("%f\n",p);
  circular_list_remove(&l,&p);

  return 0;
}
