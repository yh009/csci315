/*
 * Copyright (c) 2015 Bucknell University
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

#define MYPORT 8885

int main(int argc, char *argv[])
{
  int socket_fd;

  // address of destination socket
  struct sockaddr_in  dest;

  // pointer to host data structure
  struct hostent *hostptr;
  
  // data structure for a message
  struct message { 
    char head; 
    u_long body; 
    char tail; 
  } msgbuf;
  
  // create the socket
  socket_fd = socket (AF_INET, SOCK_DGRAM, 0);

  // zero out sockaddr structure
  memset((void*) &dest, 0, sizeof(dest));

  // return a structure of type hostent for the given host name
  hostptr = gethostbyname(argv[1]);

  // set up the proper address family in the sockaddr structure
  dest.sin_family = (short) AF_INET;

  // copy the host address bytes into the address for the socket
  bcopy(hostptr->h_addr, (char *)&dest.sin_addr,hostptr->h_length);

  // set the port number of the socket, which is the convertion of
  // integer MYPORT from host byte order to network byte order.
  // the network representation is needed for UDP socket communication
  // just for standardization.
  dest.sin_port = htons((u_short) MYPORT);
    

  // build message to send
  msgbuf.head = '<';

	// ADD COMMENT HERE: EXPLAIN WHY USE htonl TO SEND AN INTEGER IN MESSAGE
    // htonl converts the unsigned integer, which is the process id of the
    // current process, from host byte order to network byte order
    // for standardization purpose of inter-host communication.
	msgbuf.body = htonl(getpid());
  msgbuf.tail = '>';

  // UDP socket is connectionless. Hence we can send message immediately.
  // since we have no connection, the messages have to be addressed to their destination
  // sendto() allows for specifying destination. It's job is equvalent to write() in TCP
  Sendto(socket_fd, &msgbuf, sizeof(msgbuf), 0, (struct sockaddr *)&dest, sizeof(dest));

  return 0;
}

