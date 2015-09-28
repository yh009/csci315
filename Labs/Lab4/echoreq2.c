/*
 * CSCI 315 Operating Systems Design
 * Author: L. Felipe Perrone
 * Date: 2014-09-21
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual
 * or institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright
 * and permission notice is maintained, intact, in all copies and
 * supporting documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFFER_SIZE 512
#define TRUE 1
#define FALSE 0

/*------------------------------------------------------------------------
 * Program:   echoreq
 *
 * Purpose:  allocate a socket, connect to a server, transfer requested
 *            file to local host, and print file contents to stdout
 *
 * Usage:    echoreq [ host ] [ port ] [ string ]
 *
 *		 host  - name of a computer on which server is executing
 *		 port  - protocol port number server is using
 *     string - a string in double quotes
 *
 *------------------------------------------------------------------------
 */

int
main(int argc, char* argv[]) {
    
    //struct	hostent	 *ptrh;	 // pointer to a host table entry
    //struct	sockaddr_in sad; // structure to hold an IP address
    
    int sd;		                 // socket descriptor
    int port;		               // protocol port number
    char *host;                // pointer to host name
    char  in_msg[BUFFER_SIZE]; // buffer for incoming message
    char  msg[BUFFER_SIZE];
    
    //int ret_val;
    
    //memset((char *)&sad,0,sizeof(sad)); // zero out sockaddr structure
    //sad.sin_family = AF_INET;	          // set family to Internet
    
    // verify usage
    
    if (argc < 4) {
        printf("Usage: %s [ host ] [ port ] [ string ]\n", argv[0]);
        exit(-1);
    }
    
    host = argv[1];
    port = argv[2];
    
    
    if (atoi(port)<0) {
        printf("ECHOREQ: bad port number %s\n",argv[2]);
        exit(-1);
        
    }
/*    if (port > 0)
        // test for legal value
        sad.sin_port = htons((u_short)port);
    else {
        // print error message and exit
        printf("ECHOREQ: bad port number %s\n", argv[2]);
        exit(-1);
    }*/
    
    // convert host name to equivalent IP address and copy to sad
    
    // ptrh = gethostbyname(host);
    struct addrinfo ex;
    struct addrinfo *res;
    
    memset(&ex,0,sizeof ex);
    
    if (getaddrinfo(host,port,&ex,&res)) {
        printf("ECHOREQ: getaddrinfo failed\n");
        exit(-1);
    }
    
    //if ( ((char *)ptrh) == NULL ) {
    //    printf("ECHOREQ: invalid host: %s\n", host);
    //    exit(-1);
    //}
    
    // memcpy(&sad.sin_addr, ptrh->h_addr, ptrh->h_length);
    
    // create socket
//    sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sd = socket(res->ai_family,res->ai_socktype,res->ai_protocol);
    if (sd < 0) {
        printf("ECHOREQ: socket creation failed\n");
        exit(-1);
    }
    
    // connect the socket to the specified server
    
    //Connect(sd, (struct sockaddr *)&sad, sizeof(sad));
    Connect(sd, res -> ai_addr,res -> ai_addrlen);
    //	perror("ECHOREQ: connect failed");
    //	exit(-1);
    //	}
    
    // send message to server
    
    strcpy(msg,argv[3]);
    Write(sd,msg,BUFFER_SIZE);
    
    // receive message echoed back by server
    //bzero(in_msg,BUFFER_SIZE);
    Read(sd,in_msg,BUFFER_SIZE);
    printf("ECHOREQ: from server= %s\n", in_msg);
    
    // close the socket   
    close(sd);
    freeaddrinfo(res);
    
    // terminate the client program gracefully 
    return(0);
}

