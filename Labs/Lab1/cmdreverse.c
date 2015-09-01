/*Yuxuan Huang
  csci315 Prelab1*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc,char *argv[])
{
    if (argc != 2){
        printf("Err");
    }
    else{
      int i;
      for (i=strlen(argv[1]);i>=0;i--){
	printf("%c",argv[1][i]);
        }
    }
    return 0;
    }
