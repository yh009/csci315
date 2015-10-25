//Yuxuan Huang
#include <sys/time.h>
#include <time.h>

int main(int argc, char * argv){
    struct timeval {
        time_t tv_sec;
    }ut_tv;
    time_t time = (time_t)ut_tv.tv_sec;
    gettimeofday(&time,NULL);
    printf("Current time = %s",ctime(&time));
    return 0;
}