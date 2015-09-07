//Yuxuan Huang
//csci315 Lab1

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;
void print_environment(void);

int main(int argc, char* argv[]) {
    print_environment();
    pid_t child_pid,child_pid2, wpid,wpid2;int status;
    child_pid = fork();
    if (child_pid == -1) {
        perror("something went wrong in fork");
        exit(-1);
    }
    else if (child_pid == 0) {
        execlp("/bin/cat", "cat", argv[1],NULL);
        //return 0;
    }
    else{
        wpid = waitpid(child_pid,&status,0);
        //if (wpid = -1){
            //perror("wait error");
        //}
        if (status == 0){
            child_pid2 = fork();
            if (child_pid2 == -1){
                perror("fork");
                exit(-1);
            }
            else if (child_pid2 == 0){
                execlp("/usr/bin/wc","wc",argv[1],NULL);
                //return 0;
            }
            else {
                wpid2 = waitpid(child_pid2,&status,0);
                //if (wpid = -1){
                    //perror("waitpid");
                //}
                if (wpid2==0){
                    exit(0);
                }
            }
        }
    }
}
void print_environment(void){
    int i = 0;
    while(environ[i]){
        printf("%s\n",environ[i++]);
    }
}