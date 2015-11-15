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
    char *params[MAX_PARAMS+1];
    
    while(1){
        printf("ishell>");
        if(fgets(buf,50,stdin)==NULL){
            break;
        }
        if(buf[strlen(buf)-1]== '\n'){
            buf[strlen(buf)-1] = '\0';
        }
        
        tokenize(buf,params);
        
        if (strcmp(params[0],"exit")==0){
            break;
        }
        
        if(execute(params)==0){
            break;
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
        execvp(params[0],params);
        
        char* error = strerror(errno);
        printf("ishell: %s:%s\n",params[0],error);
        return 0;
    }
    
    else{//parent
        int childStatus;
        waitpid(pid,&childStatus,0);
        return 1;
    }
}