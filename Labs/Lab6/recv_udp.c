#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>

#define MYPORT 8885

/*
void printsin(struct sockaddr_in *s, char *str1, char *str2) {
  printf("%s\n", str1);
  printf("%s: ", str2);
  -- port: sin->sin_port (host integer type) 
  -- IP: sin->sin_addr (IP in dotted-decimal notation) 
  printf("\n");
}
*/
void printsin(struct sockaddr_in *sin,char *pname,char*msg);

int main(int argc, char *argv[])
{
  int socket_fd, cc, fsize;
  
	struct sockaddr_in  s_in, from;

	struct { 
		char head; 
		u_long  body; 
		char tail;
	} msg;

  // create the socket
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  // zero out the sockaddr structure
  bzero((char *) &s_in, sizeof(s_in));

  // set up the proper address family in the sockaddr strcuture
  s_in.sin_family = (short)AF_INET;

  // ADD COMMENT HERE: EXPLAIN THE EFFECT OF USING INADDR_ANY
  // set the address for the socket in the sockaddr struct
  // Using INADDR_ANY allows the program to work without knowing the IP
  // of the machine it's running on
  s_in.sin_addr.s_addr = htonl(INADDR_ANY);

  // set the port number of the socket in the sockaddr struct
  s_in.sin_port = htons((u_short) MYPORT);

  printsin( &s_in, "RECV_UDP", "Local socket is:");
  printsin((struct sockaddr_in*)&from, "RECV_UDP", "Packet from:");
  fflush(stdout);

  // ADD COMMENT HERE: EXPLAIN WHY WE NEED TO CALL bind
  // assign the address to the socket.
  // bind() assigns the specified address to the referred
  // socket
  Bind(socket_fd, (struct sockaddr *)&s_in, sizeof(s_in));

  for(;;) {
		fsize = sizeof(from);
    cc = Recvfrom(socket_fd, &msg, sizeof(msg), 0, (struct sockaddr *) &from, &fsize);
    //printsin( &from, "recv_udp: ", "Packet from:");

    // ADD COMMENT HERE: EXPLAIN WHY WE NEED TO USE ntohl TO SEND AN INTEGER IN MESSAGE
    // print out the received message
    // ntohl() convert the message from network representation back to local processor's
    //  format.
    printf("Got data ::%c%ld%c\n", msg.head, (long) ntohl(msg.body),
    msg.tail); 
    fflush(stdout);
  }
  
  return 0;
}

void printsin(struct sockaddr_in *sin,char *pname,char*msg){
    printf("\n%s:\n",pname);
    printf("%s ",msg);
    printf("IP= %s, ",inet_ntoa(sin->sin_addr));
    printf("port= %d\n",ntohs(sin->sin_port));
}

