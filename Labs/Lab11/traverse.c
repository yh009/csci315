//Yuxuan Huang
//csci315 Lab11

#include "read_dir.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>
#include <libgen.h>

// function prototypes
void process(char *name);
void enqueue(char *name, que_t *q);
void dequeue(que_t *q);
void peek_front(char *name,que_t q);
bool queue_empty(que_t q);
void initq(que_t *q);

// main function
int main(int argc,char *argv[]) {
    
    if (2 != argc) {
        printf(" usage: %s dirpath\n", argv[0]);
        exit(-1);
    }
    else {
        // pass in the starting directory
        process(argv[1]);
    }
    
    return 0;
}

// traverse a directory tree applying a function when a file is found
void process(char *root)
{
    // problem2 variables
    int numOfFiles = 0;
    int numOfReg = 0;
    int numOfDir = 0;
    unsigned long small = ULONG_MAX;
    unsigned long large = 0;
    unsigned long total = 0;
    unsigned int fd;
    char mostRecent[30];
    char leastRecent[30];
    time_t ltime;
    //ltime = time(NULL);
    time_t mtime; //= 0;
    //  end
    
    que_t nameq;
    char dname[MAXLENGTH];
    char cname[MAXLENGTH];
    char prefix[MAXLENGTH];
    
    // structure to contain the result of the fstat call (info on this file)
    struct stat file_info;
    struct stat file_info1;
    
    // structure to contain the result of the vfstat call (info on file system)
    //struct statvfs fs_info;
    
    struct dirent *dp;
    DIR *dirp;
    
    initq(&nameq);
    enqueue(root,&nameq);
    
    while (true != queue_empty(nameq)) {
        peek_front(dname,nameq);
        dequeue(&nameq);
        
        dirp = opendir(dname);
        
        if (dirp != NULL) { // it is a directory
            numOfDir++;
            if (lstat(dname,&file_info1)==0){
                if(S_ISLNK(file_info1.st_mode)){
                    continue;
                }
            }
            
            printf("directory : %s\n",dname);
            strncpy(prefix, dname, MAXLENGTH);
            strncat(prefix,"/", MAXLENGTH);
            
            for (dp = readdir(dirp); NULL != dp; dp = readdir(dirp)) {
                //numOfDir++;
                if ((strcmp(dp->d_name,"..") != 0) &&
                    (strcmp(dp->d_name,".") != 0)) {
                    
                    // prevent from infinite loop
                    strncpy(cname, prefix, MAXLENGTH);
                    
                    // concatenate the prefix
                    strncat(cname, dp->d_name, MAXLENGTH);
                    enqueue(cname,&nameq);
                }
            }
            closedir (dirp);
        } else {
            fd = open(dname,O_RDONLY);
            printf(" processing file: %s\n", dname);
            char *theName = basename(dname);
            if(fstat(fd, &file_info)==0){
                if (strcmp(basename(dname),".DS_Store") == 0){
                    continue;
                }
                else{
                    if (S_ISREG(file_info.st_mode)){
                        numOfReg++;
                    }
                    if ((unsigned long)file_info.st_size<small){
                        small = (unsigned long)file_info.st_size;
                    }
                    if ((unsigned long)file_info.st_size>large){
                        large = (unsigned long)file_info.st_size;
                    }
                    total = total + (unsigned long)file_info.st_size;
                    //printf("%s\n",basename(dname));
                    
                    //printf("%f\n",diff);
                    if(1){
                        if (numOfFiles == 0){
                            ltime = (time_t)file_info.st_mtime;
                            strcpy(leastRecent,theName);
                            //leastRecent = theName;
                            mtime = (time_t)file_info.st_mtime;
                            strcpy(mostRecent,theName);
                            //mostRecent = theName;
                        }
                        else{
                            double diffm = difftime(file_info.st_mtime,mtime);
                            //printf("%f\n",diffm);
                            double diffl = difftime(ltime,file_info.st_mtime);
                            //printf("%f\n",diffl);
                            if (diffl>0){
                                //printf("modifying least recent\n");
                                ltime = (time_t)file_info.st_mtime;
                                strcpy(leastRecent,theName);
                                //leastRecent = theName;
                            }
                            if (diffm>0){
                                //printf("modifying most recent\n");
                                mtime = (time_t)file_info.st_mtime;
                                strcpy(mostRecent,theName);
                                //mostRecent = theName;
                            }
                            
                        }
                    }
                    
                    //printf("mostRecent:%s\n",mostRecent);
                    //printf("leastRecent:%s\n",leastRecent);
                }
                
            }
            // test if it is a regular file and not a device or link -- TO-DO
            // if this is a regular file, then process it -- TO-DO
            
            numOfFiles++;
        }
    } // while
    int ave_size = (int)total / numOfFiles;
    printf(" a total of %d files were counted\n",numOfFiles);
    printf(" smallest file size: %lu\n",small);
    printf(" largerest file size: %lu\n",large);
    printf(" average file size: %d\n",ave_size);
    printf(" total number of directories: %d\n",numOfDir);
    printf(" total number of regular files: %d\n",numOfReg);
    printf(" most recently modified file: %s\n",mostRecent);
    printf(" least recently modified file: %s\n",leastRecent);
}

// initialize queue data structure
void initq(que_t *q) {
    q->head = q->tail = NULL;
}

// test whether queue data structure is empty
bool queue_empty(que_t q) {
    if (NULL == q.head) {
        return true;
    } else {
        return false;
    }
}

// add an element to queue
void enqueue(char *name, que_t *q) {
    item_t *temp;
    
    temp = (item_t *)malloc(sizeof(item_t));
    strncpy(temp->name,name,MAXLENGTH);
    temp->next = NULL;
    
    if (true == queue_empty(*q)) {
        q->head = temp;
        q->tail = temp;
    } else {
        q->tail->next = temp;
        q->tail = q->tail->next;
    }
}

// remove an element from the front of the queue
void dequeue(que_t *q) {
    item_t *temp;
    
    if (true == queue_empty(*q)) {
        printf(" error in dequeue \n");
        exit(-1);
    } else {
        temp = q->head;
        q->head = q->head->next;
        free(temp);
    }
}

// find element at front of queue without removing
void peek_front(char *name, que_t q) {
    if (true == queue_empty(q)) {
        printf(" error in dequeue \n");
        exit(-1);
    } else {
        strncpy(name, q.head->name, MAXLENGTH);
    }
} 
