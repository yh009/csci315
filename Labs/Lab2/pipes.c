//Yuxuan Huang
//csci315 prelab2

#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>


#define BUFFER_SIZE 10
#define READ_END 0
#define WRITE_END 1

int main(void){
    char write_msg[BUFFER_SIZE] = "Greetings";
    char read_msg[2];
    int fd[2];
    pid_t pid;
    int i=0;
    pid_t Fork(void);
    int Pipe(int pipefd[2]);
    int Read(int fd,void *buf, size_t count);
    int Write(int fd, const void *buf, size_t count);
    
    
    
    /*create the pipe*/
    Pipe(fd);
    //if (pipe(fd) == -1){
        //fprintf(stderr, "Pipe failed");
        //return 1;
        
    //}
    /*fork a child*/
    pid = Fork();
    //if(pid < 0){
        //fprintf(stderr, "Fork Failed");
        //return 1;
        
    //}
    if (pid > 0){/* parent process*/
        /*close the unused end of the pipe*/
        close(fd[READ_END]);
        
        /*write to the pipe*/
        //printf("a");
	    while(i<BUFFER_SIZE){
	       Write(fd[WRITE_END],write_msg+i,1);
	       i++;
	}
	//write(fd[WRITE_END],NULL,1);
        //write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
        
        /*close the write end of the pipe*/
        close(fd[WRITE_END]);
        
    }
    else{/*child process*/
        /*close the unused end of the pipe*/
        close(fd[WRITE_END]);

        /*read from the pipe*/
        while(Read(fd[READ_END],read_msg,1)!=0){
	  //read(fd[READ_END],read_msg,1);
	      printf("%c\n",read_msg[0]);
	}
        //read(fd[READ_END],read_msg,BUFFER_SIZE);
	// printf("read %s",read_msg);
        
        /*close the write end of the pipe*/
        close(fd[READ_END]);
    }
    return 0;
}


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




