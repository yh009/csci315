//Jason Hammett
//csci315
//Lab4
//September 22, 2015

#include "wrappers.h"
//#include "readwrite.h"

/* Pipe wrapper */
int Pipe(int pipefd[2]){
	int pipeResult = pipe(pipefd);
	if (pipeResult == 1) {  
		perror("Pipe creation failed\n");
		exit(-1);
		return -1;
	}
	else{
		return pipeResult;
	}
}

/* Read Wrapper */
int Read(int fd, void *buf, size_t count){
	int readResult = read(fd, buf, count);
	if (readResult == -1){
		perror("Reading failed\n");
		return -1;
	}
	else {
		return readResult;
	}
}

/* Write Wrapper */
int Write( int fd, const void *buf, size_t count){
	int writeResult = write(fd, buf, count);
	if (writeResult < 0){
		perror("Writing failed.\n");
		return -1;
	}
	else{
		return writeResult;
	}	
}


/* Fork Wrapper */
int Fork(void){
	int forkResult = fork();
	if (forkResult < 0){
		perror("Forking Failed.");
		return -1;
	}
	else{
		return forkResult;
	}
	
}

/* Wait 2 Wrapper */
pid_t Wait(int *status){
	pid_t result = wait(status);
	if (result < 0){
		// Failure
		perror("Error: Waiting failed.");
		return -1;
	}
	else{
		//Success, pid is stored in result
		return result;
	}
}

/* Close Wrapper */
int Close(int fd){
	int result = close(fd);
	if (result < 0){
		//Failure
		perror("Closing file failure.");
		return -1;
	}
	else{
		//Success
		return 0;
	}
}

/* Waitpid Wrapper */
pid_t Waitpid(pid_t pid, int *status, int options){
	int result = waitpid(pid, status, options);
	if (result == -1){
		//Failure
		perror("Waitpid failure.");
		return -1;
	}
	else{
		//Failure
		return result;
	}
}

/* Connect Wrapper */
int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int result = connect(sockfd, addr, addrlen);
	if (result == -1){
		//Failure
		perror("Failure connecting.");
		return -1;
	}
	else{
		return result;
	}
}

/* Bind Wrapper */
int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
	int result = bind(sockfd, addr, addrlen);
	if (result == -1){
		perror("Bind failed.");
		return -1;
	}
	else{
		return result;
	}
}

/* Listen Wrapper */
int Listen(int sockfd, int backlog){
	int result = listen(sockfd, backlog);
	if (result == -1){
		//Failure
		perror("Listening failed.");
		return -1;
	}
	else{
		return result;
	}
}

/* Accept Wrapper */
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
	int result = accept(sockfd, addr, addrlen);
	if (result == -1){
		perror("Accepting failed.");
		return -1;
	}
	else{
		return result;
	}
}

/* Socket Wrapper */
int Socket(int domain, int type, int protocol){
	int result = socket(domain, type, protocol);
	if (result == -1){
		perror("Socket creation failed");
		return -1;
	}
	else{
		return result;
	}
}

/* SendTo Wrapper */
ssize_t SendTo(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen){
	ssize_t result = sendto(sockfd, buf, len, flags, dest_addr, addrlen);
	if (result == -1){
		//Error Occured
		perror("Sendto failed.");
		return -1;
	}
	else{
		return result;
	}
}

/* RecvFrom Wrapper */
ssize_t RecvFrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen){
	ssize_t result = recvfrom(sockfd, buf, len, flags, src_addr, addrlen);
	if (result == -1){
		//Error occured
		perror("RecvFrom failed.");
		return -1;
	}
	else{
		return result;
	}
}

/* Writen Wrapper. 
 * This function ensures that all nbytes are wtiten to the buffer.
 * Code from Advanced Programming in the Unix Environment page 524 */
size_t Writen (int fd, void *buf, size_t nbytes){
	size_t nleft;
	size_t nwritten;

	nleft = nbytes;
	while (nleft > 0 ){
		if ((nwritten = write(fd, buf, nleft)) < 0){ //Not using Write wrapper since that masks errors and errno
			if (nleft == nbytes){
				return(-1); //error -1
			}
			else{
				break; //Error, return amount written so far
			}
		}
		else if (nwritten == 0){
			break;
		}
		nleft -= nwritten;
		buf += nwritten;//advance address to load from
	}
	return (nbytes - nleft);

}


/* REadn Wrpper
 * THis function ensures that nbytes are read from a fd, which for this function should be a network socket
 * Code from Advanced Programming in the Unix Environment on page 524 */
size_t Readn(int fd, void *ptr, size_t nbytes){
	size_t nleft;
	size_t nread;
	nleft = nbytes;
	while(nleft > 0){
		if ((nread= read(fd, ptr, nleft)) < 0 ){
			if (nleft == nbytes){
				return (-1); // error return -1
			}
			else
				break; //error, return amount of bytes read so far
		}
		else if (nread == 0){
			break; //end of file
		}
		nleft -= nread;
		ptr += nread; //move forward pointer in buffer
	}
	return (nbytes - nleft); //return >= 0
}

/* Execvp Wrapper 
 * The man dictates that if execlp returns, an error occured and the value is -1*/
int Execvp(const char *file, char *const argv[]){
	int result = execvp(file, argv);
	//Check return value
	if (result == -1){
		//Error occured
		perror("Execvp: error executing program");
		return -1;
	}
	else{
		//No error
		return 0;
	}
}

