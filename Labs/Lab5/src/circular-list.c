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
#include "circular-list.h" 

int circular_list_create(struct circular_list *l, int size) {
  l->buffer = calloc(size, sizeof(item));
  l->start = -1;
  l->end = -1;
  l->elems = 0;
  l->size = size;
  return 0;
}

int circular_list_insert(struct circular_list *l, item i) {
  if(l->elems==0){
    l->start=0;
    l->end=0;
    l->elems=l->elems+1;
    l->buffer[l->end]=i;
  }
  else if(l->elems==l->size){
    printf("list full\n");
    return 0;
  }
  else{
    int newEnd=(l->end+1)%(l->size);
    l->buffer[newEnd]=i;
    l->end=newEnd;
    l->elems=l->elems+1;
  }
  return 0;
}

int circular_list_remove(struct circular_list *l, item *i) {
  if(l->elems==1){
    *i=l->buffer[l->start];
    l->elems=l->elems-1;
    l->buffer[l->start]=0;
    l->start=-1;
    l->end=-1;
  }
  else if(l->elems==0){
    printf("empty\n");
    return 0;
  }
  else{
    *i=l->buffer[l->start];
    l->buffer[l->start]=0;
    l->elems=l->elems-1;
    l->start=(l->start+1)%(l->size);
  }
  return 0;
}
