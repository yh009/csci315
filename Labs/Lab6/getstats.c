#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "readwrite.h"
#include "wrappers.h"

/*------------------------------------------------------------------------
 * Program:   getstats 
 *
 * Purpose:   allocate a socket, connect to a server, 
 *            request file transfer statistics
 *
 * Syntax:    getstats [ host ] [ port ]
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *
 *------------------------------------------------------------------------
 */

#define BUFSIZE 1000
#define NAMELEN 257

int main(int argc, char* argv[]) {

  struct	hostent	 *ptrh;	 // pointer to a host table entry	
  struct	sockaddr_in sad; // structure to hold an IP address	

  struct addrinfo hint;
  struct addrinfo *serverptr;

  int	sd;		           // socket descriptor			
  int	port;		         // protocol port number		
  char	*host;		     // pointer to host name		
  int	n;		           // number of characters read		
  char	buf[BUFSIZE];  // buffer for data from the server	
  int   bytes_read;    // number of bytes read from socket
  int   bytes_expected;

  memset((char *)&sad,0,sizeof(sad)); // clear sockaddr structure	
  sad.sin_family = AF_INET;	      // set family to Internet	
  
  // Check command-line arguments
  
  if (argc < 3) {
    printf("usage: getstats [ host ] [ port ]\n");
    exit(-1);
  }

  host = argv[1];		
  port = atoi(argv[2]);	

  if (port <= 0) {	
    // test for legal value		
    // print error message and exit	
    fprintf(stderr,"GETSTATS: bad port number %s\n",argv[2]);
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
    fprintf(stderr, "GETSTATS: socket creation failed\n");
    exit(1);
  }
  
  // Connect the socket to the specified server. 
  
  if (connect(sd, (struct sockaddr *)(&sad), sizeof(struct sockaddr)) < 0) {
    fprintf(stderr,"GETSTATS: connect failed\n");
    exit(1);
  }
  
  // Repeatedly read data from socket and write to user's screen. 
 
  strcpy(buf, "stats");
  bytes_expected = 5;

  Writen(sd, &bytes_expected, sizeof(int));
  Writen(sd, buf, strlen(buf));

  bytes_read = Readn(sd, &bytes_expected, sizeof(int));
  
  do {
    bytes_read = Readn(sd, buf, bytes_expected);
    if (bytes_read > 0)
    {
      buf[bytes_read] = 0; // terminate the string
      printf("%s", buf);
    }
  } while (bytes_read > 0);

  // Close the socket. 
  
  Close(sd);
  
  // Terminate the client program gracefully. 
  
  exit(0);
}
