#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <ctype.h>
#include "wrappers.h"




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

int Wait(int *status){
  int result = wait(status);
  if (result<0){
    perror("wait");
    exit(-1);
  }
  return 0;
}

int Waitpid(pid_t pid,int *status, int options){
  int result = waitpid(pid,status,options);
  if (result<0){
    perror("waitpid");
    exit(-1);
  }
  return 0;
}

int Open(const char *pathname, int flags,mode_t mode){
  if (open(pathname,flags,mode)<0){
    perror("open");
    exit(-1);
  }
  return 0;
}

int Close(int fd){
  int result = close(fd);
  if(result<0){
    perror("close");
    exit(-1);
  }
  return 0;
}


int Connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
  int result = connect(sockfd,addr,addrlen);
  if(result<0){
    perror("connect");
    exit(-1);
  }
  return 0;
}

int Bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen){
  int result = bind(sockfd,addr,addrlen);
  if(result<0){
    perror("bind");
    exit(-1);
  }
  return 0;
}

int Listen(int sockfd,int backlog){
  int result = listen(sockfd,backlog);
  if(result<0){
    perror("listen");
    exit(-1);
  }
  return 0;
}

int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen){
  int result = accept(sockfd,addr,addrlen);
  if(result<0){
    perror("accept");
    exit(-1);
  }
  return 0;
}
