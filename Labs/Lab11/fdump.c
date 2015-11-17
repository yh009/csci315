//Yuxuan Huang
//csci315 Lab11

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>
#include "hexdump.h"



int main(int argc, char *argv[]){
    char *filename;
    unsigned int offset;
    unsigned int size;
    
    if(argc < 4){
        printf("usage: fdump: [filename] [offset] [size]\n");
        return -1;
    }
    
    filename = argv[1];
    offset = atoi(argv[2]);
    size = atoi(argv[3]);
    
    unsigned char buf[size+1];
    
    FILE *fd = fopen((char *)filename,"r");
    
    fseek(fd,offset,SEEK_SET);
    fread(buf,size,1,fd);
    
    hexdump(buf,size);
    printf("\n");
    fclose(fd);
    return 0;
}
    
