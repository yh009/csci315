//Yuxuan Huang
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>


void* thread1(void *arg);
void* thread2(void *arg);
void* thread3(void *arg);

//pthread_t th1,th2,th3;

int main(int argc, char* argv[]) {
    pthread_t th1,th2,th3;
    int sum=0;
    int j;
    int end=10000;
    pthread_create(&th1,NULL,&thread1,NULL);
    pthread_create(&th2,NULL,&thread2,NULL);
    pthread_create(&th3,NULL,&thread3,NULL);
    while(1){
        for(j=1;j<=end;j++){
            sum=sum+j;
        }
        sum=0;
    }
}


void* thread1(void *arg){
    int num[] = {0,1,2,3,4,5,6,7,8,9};
    int i=0;
    int sum=0;
    int j;
    int end=10000;
    while(1){
        if(i<10){
            printf("%d\n",num[i]);
            i++;
            for(j=1;j<=end;j++){
                sum=sum+j;
            }
            sum=0;
        }
        else{
            printf("%d\n",num[i]);
            i=0;
            for(j=1;j<=end;j++){
                sum=sum+j;
            }
            sum=0;
        }
    }
}



void* thread2(void *arg){
    char alpha[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
    int i=0;
    int sum=0;
    int j;
    int end=10000;
    while(1){
        if(i<26){
            printf("%c\n",alpha[i]);
            i++;
            for(j=1;j<=end;j++){
                sum=sum+j;
            }
            sum=0;
        }
        else{
            printf("%c\n",alpha[i]);
            i=0;
            for(j=1;j<=end;j++){
                sum=sum+j;
            }
            sum=0;
        }
    }
}

void* thread3(void *arg){
    int sum=0;
    int j;
    int end=10000;
    while(1){
        printf("#\n");
        for(j=1;j<=end;j++){
            sum=sum+j;
        }
        sum=0;
    }
}