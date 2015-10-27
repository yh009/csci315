#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include "readwrite.h"
#include "wrappers.h"

#define MAX_FILE_PATH   257 // length of path+filename and null char  
#define BUFFER_SIZE     512 // size of file read buffer    
#define	QLEN		6   // size of request queue
#define MAX_THREAD      5   // max number of concurrent threads
int	visits	    =   0;  // counts client connections

/*------------------------------------------------------------------------
 * Program:   fileserver
 *
 * Purpose:   allocate a socket and then repeatedly execute the following:
 *		(1) wait for the next connection from a client
 *		(2) send a short message to the client
 *		(3) close the connection
 *		(4) go back to step (1)
 *
 * Syntax:    fileserver [ port ]
 *
 *		 port  - protocol port number to use
 *
 *------------------------------------------------------------------------
 */
pthread_mutex_t *lock[4];
sem_t *visit;

int num_file_req=0;
int num_stat_req=0;
int num_file_not_found=0;
int total_len=0;
double ave_len;

void process_request(int fd);
void *threads(void *arg);
void report();


int main(int argc, char* argv[]) {
	struct sockaddr_in sad;  // structure to hold server's address	
	struct sockaddr_in cad;  // structure to hold client's address	
	int sd, sd2;	           // socket descriptors
	int port;		             // protocol port number		
	socklen_t alen;          // length of address			
	int pid;                 // process id
    int i;
    int count;
    
    //initializations
    for(i=0;i<4;i++){
        pthread_mutex_init(lock[i],NULL);
    }
    sem_init(visit,0,MAX_THREAD);

    
    

	memset((char *)&sad,0,sizeof(sad)); // clear sockaddr structure	
	sad.sin_family = AF_INET;	          // set family to Internet	        
	sad.sin_addr.s_addr = INADDR_ANY;   	

	// Check command-line argument for protocol port
	if (argc > 1) {			
		port = atoi(argv[1]);	        
	}
	else {
		printf("Usage: fileserver [ port ]\n");
		exit(-1);
	}

	if (port > 0)	
		// test for illegal value	
		sad.sin_port = htons((u_short)port);
	else {				
		// print error message and exit	
		fprintf(stderr,"SERVER: bad port number %s\n",argv[1]);
		exit(1);
	}

	// Create a socket 
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd < 0) {
		fprintf(stderr, "SERVER: socket creation failed\n");
		exit(1);
	}

	// Bind a local address to the socket 
    Bind(sd, (struct sockaddr *)&sad, sizeof(sad));

	// Specify size of request queue 
    Listen(sd, QLEN);

    
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_t *tid=(pthread_t *)calloc(MAX_THREAD,sizeof(pthread_t));
	// Main server loop - accept and handle requests
	while (1) { // it is a daemon, so infinite loop is ok
        alen = sizeof(cad);
        
        sem_wait(visit);
        pthread_mutex_lock(lock[0]);
        count = visits % MAX_THREAD;
        int *sd3 = (int*)malloc(sizeof(int));
        *sd3=Accept(sd,(struct sockaddr *)&cad,&alen);
        visit++;
        
        pthread_create(&tid[count],&attr,threads,(void*)sd3);
    }
    Close(sd); // child closes listening socket descriptor
    pthread_exit(NULL);
	return(0); // will never get here, but to shut up the compiler
}

void *threads(void *arg){
    int *sd3 = (int*)arg;
    process_request(*sd3);
    Close(*sd3);// done serving this client
    free(sd3);
    sem_post(visit);
    pthread_exit(NULL);
}

void process_request(int fd)
{
	char buf[BUFFER_SIZE];  // buffer for file chunk server sends	
	char reqbuf[MAX_FILE_PATH];
	int file_req;
	int bytes_read;     
	int bytes_expected;

	// Read request for fileserver
	// first red the length of incoming string

	Readn(fd, &bytes_expected, sizeof(int));
	Readn(fd, reqbuf, bytes_expected);

	reqbuf[bytes_expected] = 0;

	if (strncmp(reqbuf, "get", 4) == 0) {
		// Request is "get file", so now read full path to file
		// Pre-condition: full path string is no more than 256 chars long
		// now read the length of the file name
		Readn(fd, &bytes_expected, sizeof(int));

		// read the actual file name
		Readn(fd, reqbuf, bytes_expected);

		reqbuf[bytes_expected] = 0; // terminate the string

		printf("SERVER: file requested is %s\n", reqbuf);
		fflush(stdout);

		if ((file_req = open(reqbuf,O_RDONLY)) == -1) {
            pthread_mutex_lock(lock[1]);
            num_file_req++;
            pthread_mutex_unlock(lock[1]);
            
            pthread_mutex_lock(lock[2]);
            num_file_not_found++;
            pthread_mutex_unlock(lock[2]);
            
			printf("SERVER: file not found\n");
            //report();
            pthread_mutex_unlock(lock[0]);
			fflush(stdout);
		} 
		else {
			printf("SERVER: file %s found\n", reqbuf);
			fflush(stdout);
            
            int file_len = 0;

			do {
				bytes_read = Readn(file_req, buf, BUFFER_SIZE);
                file_len += bytes_read;
				Writen(fd, buf, bytes_read);
			} while (bytes_read > 0);
            pthread_mutex_lock(lock[1]);
            num_file_req++;
            pthread_mutex_unlock(lock[1]);
            pthread_mutex_lock(lock[3]);
            total_len +=file_len;
            ave_len = (double)total_len/((double)num_file_req - (double)num_file_not_found);
            pthread_mutex_unlock(lock[3]);
            //report();
            pthread_mutex_unlock(lock[0]);
            fflush(stdout);

        }
    }
	else if (strncmp(reqbuf, "stats", 6) == 0) {
		// Request is "get stats"
        pthread_mutex_lock(lock[4]);
        num_stat_req++;
        pthread_mutex_unlock(lock[4]);
        
		printf("SERVER: stats requested");

		sprintf(buf,"Server has been contacted %d time%s\n",
				visits,visits==1?".":"s.");
        
        report();

		bytes_expected = strlen(buf);
		Writen(fd, &bytes_expected, sizeof(int));
		Writen(fd, buf, bytes_expected);
        pthread_mutex_unlock(lock[0]);
	}
	else {
		// Request is invalid
		printf("SERVER: invalid request\n");
	}
}

void report(){
    printf("number of file requests served: %d\n",num_file_req);
    printf("number of status requests served: %d\n",num_stat_req);
    printf("number of file not found errors: %d\n",num_file_not_found);
    printf("average length of files requested: %f\n",ave_len);
    fflush(stdout);
}
