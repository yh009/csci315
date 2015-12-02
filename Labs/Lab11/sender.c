//Yuxuan Huang
//Lab11 
//Problem 4

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>

int main(int argc, char *argv[]){
    char buf[1024];
    sem_t *s = sem_open("mysem",O_CREAT,S_IRWXU | S_IRWXG | S_IRWXO,1);
    
    if(s==SEM_FAILED){
        perror("sem_open");
        exit(-1);
    }
    
    int fd = open("channel.txt",O_CREAT | O_WRONLY);
    
    if(fd==-1){
        perror("open");
        exit(-1);
    }
    while(1){
        printf(">sender ");
        fgets(buf,sizeof(buf),stdin);
        
        if(strlen(buf)!=0){
            sem_wait(s);
            write(fd,buf,strlen(buf));
            sem_post(s);
        }
    }
    
}
