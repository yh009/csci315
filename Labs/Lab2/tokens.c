//Yuxuan Huang
//csci315 prelab2

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/wait.h>


#define BUFFER_SIZE 35
#define READ_END 0
#define WRITE_END 1
pid_t Fork(void){
    pid_t the_fork;
    
    the_fork = fork();
    
    if (the_fork == -1){
        perror("fork");
        exit(-1);
    }
    return the_fork;
}

int Pipe(int pipefd[2]){
    
    if (pipe(pipefd)==-1){
        perror("pipe");
        exit(-1);
    }
    return 0;
}

int Read(int fd,void *buf, size_t count){
    int result = read(fd,buf,count);
    if (result < 0){
        perror("read");
        exit(-1);
    }
    return result;
}

int Write(int fd, const void *buf, size_t count){
    int result = write(fd,buf,count);
    if (result < 0){
        perror("write");
        exit(-1);
    }
    return result;
}


int main(void){
    char write_msg[BUFFER_SIZE];
    char read_msg[BUFFER_SIZE];
    int fd[2];
    int fd2[2];
    pid_t pid;
    //int i=0;
    const char s[2] = " ";
    char *token;
    char result[0];
    int num;
    /*create the pipe*/
    Pipe(fd);
    Pipe(fd2);
    
    //fflush(stdout);
    Read(STDIN_FILENO,write_msg,BUFFER_SIZE);
    //scanf("%s",write_msg);
    printf("string entered:%s\n",write_msg);
    
    pid = Fork();
    
    
    if (pid > 0){/* parent process*/
        /*close the unused end of the pipe*/
        close(fd[READ_END]);
        close(fd2[WRITE_END]);
        while (1){
            
            int length = strlen(write_msg)+1;
            printf("length:%d\n",length);
            
            Write(fd[WRITE_END],&length,4);
            printf("p to c write length:%d\n",length);
            Write(fd[WRITE_END],write_msg,length);
            printf("p to c write:%s\n",write_msg);
            //close(fd[WRITE_END]);
            
            Read(fd2[READ_END],&num,4);
            printf("c to p read length:%d\n",num);
            char buff[35];
            Read(fd2[READ_END],&buff,num);
            printf("c to p receive:%s\n",buff);


        }
        close(fd2[READ_END]);
        close(fd[WRITE_END]);
    }
    
                  

    
    else {/*child process*/
        /*close the unused end of the pipe*/
        close(fd[WRITE_END]);
        close(fd2[READ_END]);
        /*read from the pipe*/
        while(1){
            Read(fd[READ_END],&num,4);
            printf("p to c receive length:%d\n",num);
            
            Read(fd[READ_END],read_msg,num);
            printf("p to c reveive:%s\n",read_msg);
            
            token = strtok(read_msg,s);
            while(token != NULL){
                strcat(result,token);
                strcat(result,s);
                token = strtok(NULL, s);
                //printf("result:%s\n",result);
            }
            printf("result:%s\n",result);
            //close(fd[READ_END]);
            int length2 = strlen(result)+1;
            Write(fd2[WRITE_END],&length2,4);
            printf("c to p write length:%d\n",length2);
            Write(fd2[WRITE_END],result,length2);
            printf("c to p write:%s\n",result);
            
        }
        close(fd[READ_END]);
        close(fd2[WRITE_END]);
    }
    return 0;
}

