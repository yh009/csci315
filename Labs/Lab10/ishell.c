//Yuxuan Huang
//Lab10


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_PARAMS 10

void tokenize(char *cmd, char** params);
int execute(char** params);

int main(int argc, char** argv){
    char buf[50];
    char *buf1;
    char *buf2;
    char *params[MAX_PARAMS+1];
    int two_cmd=0;
    
    while(1){
        printf("ishell>");
        if(fgets(buf,50,stdin)==NULL){
            break;
        }
        if(buf[strlen(buf)-1]== '\n'){
            buf[strlen(buf)-1] = '\0';
        }
        if(buf[0]==0){
            continue;
        }
        
        int j;
        for(j=0;j<strlen(buf);j++){
            if(buf[j]==';'){
                two_cmd=1;
                break;
            }
        }
        if(two_cmd==1){
            buf1=strtok(buf,";");
            //printf("%s\n",buf1);
            buf2=strtok(NULL,";");
            //printf("%s\n",buf2);
            tokenize(buf1,params);
            if (strcmp(params[0],"exit")==0){
                break;
            }
            if(execute(params)==0){
                break;
            }
            tokenize(buf2,params);
            if (strcmp(params[0],"exit")==0){
                break;
            }
            if(execute(params)==0){
                break;
            }
            //two_cmd=0;
        }
        
        else{
            tokenize(buf,params);
            printf("%s\n",params[0]);
            if (strcmp(params[0],"exit")==0){
                break;
            }
            if(execute(params)==0){
                break;
            }
        }
    }
    return 0;
}

void tokenize(char *cmd, char** params){
    int i;
    params[0] = strtok(cmd," ");
    for (i=1;i<10;i++){
        params[i] = strtok(NULL," ");
        if(params[i] == NULL){
            break;
        }
    }
}

int execute(char** params){
    pid_t pid = fork();
    
    if (pid == -1){
        perror("fork");
        exit(-1);
    }
    
    else if(pid==0){//child
        if(execvp(params[0],params)==-1){
            char* error = strerror(errno);
            printf("[ishell: program terminated abnormally] [%d:%s]\n",errno,error);
            return -1;
        }
        return 0;
    }
    
    else{//parent
        int childStatus;
        int c = waitpid(pid,&childStatus,0);
        if(c!=-1){
            printf("[ishell: program termiated successfully]\n");
        }
        return 1;
    }
}