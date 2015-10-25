#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readwrite.h"

/*------------------------------------------------------------------------
 * Program:   getfile 
 *
 * Purpose:   allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Syntax:    getfile [ host ] [ port ] [ file ] 
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *               file  - complete path of file to retrieve
 *
 *------------------------------------------------------------------------
 */

#define BUFSIZE 1000
#define NAMELEN 257

int main(int argc, char* argv[]) {

  struct	sockaddr_in sad; // structure to hold an IP address	
  struct addrinfo hint;
  struct addrinfo *serverptr;

  int	sd;		                 // socket descriptor			
  int	port;		               // protocol port number		
  char	*host;		           // pointer to host name		
  char	buf[BUFSIZE];	       // buffer for data from the server	
  char  file_name[NAMELEN];  // buffer for full path to file
  int   bytes_read;          // number of bytes read from socket
  int   bytes_expected;

  memset((char *)&sad,0,sizeof(sad)); // clear sockaddr structure	
  sad.sin_family = AF_INET;	          // set family to Internet	
  
  // Check command-line arguments
  
  if (argc < 4) {
    printf("usage: getfile [ host ] [ port ] [ file ]\n");
    exit(-1);
  }

  host = argv[1];		
  port = atoi(argv[2]);	
  strncpy(file_name, argv[3], 257);

  if (port <= 0) {	
    // test for legal value		
    // print error message and exit	
    fprintf(stderr,"GETFILE: bad port number %s\n",argv[2]);
    exit(1);
  }

  //  prepare the hint information
  bzero(&hint, sizeof(hint));
  hint.ai_flags = AI_CANONNAME;
  hint.ai_family = AF_INET;

  if (getaddrinfo(host, NULL, &hint, &serverptr) < 0)
  {
       fprintf(stderr, "getaddrinfo error");
       exit(1);
  }

  bcopy(serverptr->ai_addr, (char *)&sad, serverptr->ai_addrlen);

  sad.sin_port = htons((u_short)port);

  // Create a socket. 
  
  sd = socket(AF_INET, SOCK_STREAM, 0);
  if (sd < 0) {
    fprintf(stderr, "GETFILE: socket creation failed\n");
    exit(1);
  }
  
  // Connect the socket to the specified server. 
  
  if (connect(sd, (struct sockaddr *)(&sad), sizeof(struct sockaddr)) < 0) {
    fprintf(stderr,"GETFILE: connect failed\n");
    exit(1);
  }
  
  strcpy(buf, "get");
  bytes_expected = 3;

  // Repeatedly read data from socket and write to stdout
  Writen(sd, &bytes_expected, sizeof(int));
  Writen(sd, buf, strlen(buf));

  bytes_expected = strlen(file_name);
  strncpy(buf, file_name, bytes_expected);

  Writen(sd, &bytes_expected, sizeof(int));
  Writen(sd, buf, bytes_expected);
   
  do {
    bytes_read = Readn(sd, buf, BUFSIZE);
    if (bytes_read > 0)
    {
      buf[bytes_read] = 0; // terminate the string
      printf("%s", buf);
    }
  } while (bytes_read > 0);

  // Close the socket 
  
  close(sd);
  
  // Terminate the client program gracefully 
  
  exit(0);
}
