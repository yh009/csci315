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
//#include <make.h>


#define BUFFER_SIZE 10
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
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[2];
    int fd[2];
    int fd2[2];
    pid_t pid;
    int i=0;
    //int j=0;
    //int k=0;
    //char storage[BUFFER_SIZE];
    /*create the pipe*/
    Pipe(fd);
    Pipe(fd2);
    
    pid = Fork();


    if (pid > 0){/* parent process*/
            /*close the unused end of the pipe*/
            close(fd[READ_END]);
            close(fd2[WRITE_END]);
            /*write to the pipe*/
            //if(Read(fd[READ_END],read_msg,1)<=0){
            while(i<BUFFER_SIZE){
                Write(fd[WRITE_END],write_msg+i,1);
                i++;
            }
            close(fd[WRITE_END]);
            char buff;
            while(Read(fd2[READ_END],&buff,1)>0){
                printf("%c\n",buff);
            }
            close(fd2[READ_END]);
                //return 0;
            
    }

    else {/*child process*/
            /*close the unused end of the pipe*/
        close(fd[WRITE_END]);
        close(fd2[READ_END]);
            /*read from the pipe*/
        while(Read(fd[READ_END],read_msg,1)>0){
            printf("%c\n",read_msg[0]);
            char upper=toupper(read_msg[0]);
            Write(fd2[WRITE_END],&upper,1);
        }
        close(fd[READ_END]);
        /*close the write end of the pipe*/
        //while(j<BUFFER_SIZE){
            //Write(fd2[WRITE_END],storage+j,1);
            //j++;
        //}
        close(fd2[WRITE_END]);
                //return 0;
    }
    return 0;
}


    
    
/*    if (pid < 0){
                close(fd2[READ_END]);
                close(fd[READ_END]);
                close(fd[WRITE_END]);
             
                while(i<BUFFER_SIZE){
                    Write(fd2[WRITE_END],storage+i,1);
                    i++;
                }
                close(fd2[WRITE_END]);
    }
    else{
                close(fd2[WRITE_END]);
                close(fd[READ_END]);
                close(fd[WRITE_END]);
             
                while(Read(fd2[READ_END],read_msg,1)!=0){
                    printf("%c\n",read_msg[0]);
                }
                close(fd2[READ_END]);
    }
    return 0;
}
*/
