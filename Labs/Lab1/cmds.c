/*Yuxuan Huang
  csci315 prelab1*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{

  if (argc != 5) {
      printf("Err");
    }
  else {
    char the_char = *argv[1];
    int the_int = strtol(argv[2],NULL,10);
    float the_float =strtof(argv[3],NULL);
    char *the_str = argv[4];

    printf("charater:%c, integer:%i,float:%f,string:%s\n",the_char,the_int,the_float,the_str);

  }
  return 0;
}

  
  
