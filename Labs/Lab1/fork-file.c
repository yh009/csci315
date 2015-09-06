/*
 * CSCI 315 Operating Systems Design
 * Date: 2014-09-02
 * Copyright (c) 2014 Bucknell University
 *
 * Permission is hereby granted, free of charge, to any individual or
 * institution obtaining a copy of this software and associated
 * documentation files (the "Software"), to use, copy, modify, and
 * distribute without restriction, provided that this copyright and
 * permission notice is maintained, intact, in all copies and supporting
 * documentation.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL BUCKNELL UNIVERSITY BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int i = 7;
double x = 3.14;

int main(int argc, char* argv[]) {
    
    int pid;
    int j = 6;
    double y = 2.18;
    
    char buf_parent[6];
    char buf_child[6];
    int status; // exit status to be filled by wait
    
    FILE *fp = fopen("data.txt","w+");
    char str[]="this is a test for processes created with fork\nthis is another line";
    fwrite(str,1,sizeof(str),fp);
    
    // create and open a file called data.txt
    // use open (file descriptors)
    
    // write into data.txt the following string:
    // "this is a test for processes created with fork\nthis is another line"
    
    
    if ((pid = fork()) == 0) {
        // child process
        fseek(fp,SEEK_SET,0);
        fread(buf_child,5,1,fp);
        printf("%s\n",buf_child);
        // read 5 characters from file into buf_child
        // print the characters in buf_child to terminal
        
        //printf("pid= %d -- initially, child sees x= %lf, y=%lf\n", pid, x, y);
        //x = 0;
        //y = 0;
        //printf("pid= %d -- child sees x= %lf, y=%lf\n", pid, x, y);
        fclose(fp);
        printf("child is terminating\n");
        
        // close the file
        
        exit(0);
        
    } else {
        
        // parent process
        fseek(fp,SEEK_SET,0);
        fread(buf_parent,5,1,fp);
        printf("%s\n",buf_parent);
        // read 5 characters from file into buf_parent
        // print the characters in buf_child to terminal
        
        //printf("pid= %d -- parent waits for child to terminate\n", pid);
        //printf("pid= %d -- before wait parent sees x= %lf, y=%lf\n", pid, x, y);
        
        //wait(&status); // note we are not catching the return value of wait!
        //printf("parent got termination status= %d from child\n", status);
        //printf("pid= %d -- after wait sees x= %lf, y=%lf\n", pid, x, y);
        
        // read another 5 characters from file into buf_parent
        // print the characters in buf_parent to terminal
        fclose(fp);
        // close the file
        
        printf("parent is terminating\n");
        exit(0);
    }
    
    return 0;
}

int wrapper(void){
    
    if (pid_t Fork(void)==-1){
        perror("error: ");
        printf("errno = %d.\n",errno);
        exit(-1);
    };
    
}
