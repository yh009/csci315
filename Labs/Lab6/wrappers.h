#ifndef _WRAPPERS_H_
#define _WRAPPERS_H_

pid_t Fork(void);

int Pipe(int pipefd[2]);

int Read(int fd,void *buf, size_t count);

int Write(int fd, const void *buf, size_t count);

int Wait(int *status);

int Waitpid(pid_t pid,int *status, int options);

int Open(const char *pathname, int flags,mode_t mode);

int Close(int fd);

int Connect(int sockfd,const struct sockaddr *addr,socklen_t addrlen);

int Bind(int sockfd,const struct sockaddr *addr,socklen_t addrlen);

int Listen(int sockfd,int backlog);

int Accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

//int Socket(int domain,int type,int protocol);

int Sendto(int sockfd,const void *buf,size_t len,int flags,const struct sockaddr *dest_addr,socklen_t addrlen);

int Recvfrom(int sockfd, void *buf, size_t len,int flags,struct sockaddr *src_addr,socklen_t *addrlen);

#endif