//Jason Hammett
//csci315
//Lab4
//September 22, 2015
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#ifndef WRAPPERS_H_
#define WRAPPERS_H_

/* Pipe wrapper */
int Pipe(int pipefd[2]);

/* Read Wrapper */
int Read(int fd, void *buf, size_t count);


/* Write Wrapper */
int Write( int fd, const void *buf, size_t count);

/* Fork wrapper */
int Fork(void);

/* Close Wrapper */
int Close(int fd);

/* Wait Wrapper */
pid_t Wait(int *status);

/* Waitpid Wrapper */
pid_t Waitpid(pid_t pid, int *status, int options);

/* Connect Wrapper */
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/* Bind Wrapper */
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

/* Listen Wrapper */
int Listen(int sockfd, int backlog);

/* Accept Wrapper */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

/* Socket Wrapper */
int Socket(int domain, int type, int protocol);

/* SendTo Wrapper */
ssize_t SendTo(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);

/* RecvFrom Wrapper */
ssize_t RecvFrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);

/*  The following wrapper is for Reading from a networked socket and ensuring that all bytes arrive.
 *  It is defined in The Advanced Programming in the Unix Env textbook on page 524. */
//ssize_t Readn (int fd, void *buf, size_t nbytes);

/* The following wrapper is for writing to a networked socket and ensuring all bytes are sent.
 * It is defined in the Advanced Programming in the Unix Environment on page 524. */
//ssize_t Writen (int fd, void *buf, size_t nbytes);

/* Execlp Wrapper */
int Execvp(const char *file, char *const argv[]);

#endif
