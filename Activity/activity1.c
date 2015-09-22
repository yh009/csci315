//Henry Kwan, Yuxuan Huang
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int main(int argc, char* argv[]) {
    void *summation1(void *ptr);
    void *summation2(void *ptr);
    void *n = atoi(argv[1]);
    pthread_t th1, th2;
    void *status;
    pthread_create(&th1, NULL,*summation1,&n);
    pthread_join(th1, &status);
    int dv1 = (int*)status;
    pthread_create(&th2, NULL,*summation2,&n);
    pthread_join(th2, &status);
    int dv2 = (int*)status;
    int sum = dv1+dv2;
    printf("%d\n", sum);
    return 0;
}
int sum1 =0;
int sum2 =0;
void *summation1(void *ptr){
    //int sum = 0;
    int the_n = &n;
    int i = 1;
    int j = n/2-1;
    for (i; i < j; i++){
        sum += i;
    }
    return (void*)sum;
}
void *summation2(void *ptr){
    //int sum = 0;
    int the_n = &n;
    int i = n/2-1;
    int j = n;
    for (i; i < j; i++){
        sum += i;
    }
    return (void*)sum;
}
