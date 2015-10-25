#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

ssize_t				
readn(int fd, void *vptr, size_t n)
{
	size_t	nleft;
	ssize_t	nread;
	char	*ptr;

	ptr = vptr;
	nleft = n;
	while (nleft > 0) {
		nread = read(fd, ptr, nleft);
		//fprintf(stderr, "nread %ld\n", nread);
		if (nread  < 0) {
			if (errno == EINTR)
				nread = 0; /* and call read() again */
			else
				return(-1);
		} else if (nread == 0)
			break; /* EOF */

		nleft -= nread;
		ptr   += nread;
	}
	return(n - nleft); /* return >= 0 */
}

ssize_t
Readn(int fd, void *ptr, size_t nbytes)
{
	ssize_t		n;

	if ( (n = readn(fd, ptr, nbytes)) < 0) {
		printf("readn error\n");
		exit(-1);
	}
	return(n);
}

ssize_t						
writen(int fd, const void *vptr, size_t n)
{
  size_t		nleft;
  ssize_t		nwritten;
  const char	*ptr;
  
  ptr = vptr;
  nleft = n;
  while (nleft > 0) {
    nwritten = write(fd, ptr, nleft);
    //fprintf(stderr, "bytes written %ld\n", nwritten);
    if ( nwritten <= 0) {
      if (nwritten < 0 && errno == EINTR)
				nwritten = 0;		/* and call write() again */
			else
				return(-1);			/* error */
    }
    
    nleft -= nwritten;
    ptr   += nwritten;
  }
  return(n);
}

void
Writen(int fd, void *ptr, size_t nbytes)
{
  if (writen(fd, ptr, nbytes) != nbytes) {
    printf("writen error\n");
    exit(-1);
  }
}
