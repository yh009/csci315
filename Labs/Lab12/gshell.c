/*
 * Jason Hammett
 * Ravi Lonberg
 * Henry Kwan
 * Yuxuan Huang
 * csci315
 * Lab 12
 */
#include "wrappers.h"
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include "print.h"

#define MAX_PARAMS 10

pid_t pid; //process ids

//int pipefd[2];

void forkAndRun(char *args[]);
int runProgram(char *args[]);
void tokenize(char *cmd, char** params);
int execute(char** params1,char** params2);
//int execute2(char** params);



int main(int argc, char *argv[]){
	char *line = malloc(sizeof(char)*50);
	size_t len = 0;
	char *savePtr1, *savePtr2; //used in thread safe tokenizer
	int inNewLineBool = 0;; //used to detect two newline hits
    char cwd[100];
    int prob2 = 0;
    char *params1[MAX_PARAMS+1];
    char *params2[MAX_PARAMS+1];
	while (1){
		memset(cwd,0,100);
        getcwd(cwd,100);
        printf("gshell %s> ",cwd);
		char *args[20];
		size_t charsRead = getline(&line, &len, stdin);
		//First check if anything was provided
		/*
		if (strcmp(line, "\n") == 0){
			continue;
		}
		*/
		//Boolean operation to detect if two newlines have been netered consecutively,
		if (strcmp(line, "\n") == 0){
			if (inNewLineBool == 0){
				inNewLineBool++;
				continue;
			}
			else if (inNewLineBool == 1){
				args[0] = "ls";
				args[1] = "-lsa";
				args[2] = NULL;
				forkAndRun(args);
				inNewLineBool = 0;
				continue;
			}
		}
		else{
			inNewLineBool = 0;
			if (line[charsRead -1] == '\n'){
				line[charsRead - 1] = 0;
			}
			char *lineCpy = malloc(strlen(line) + 1);
			strcpy(lineCpy, line);
            int j;
            for(j=0;j<strlen(line);j++){
                if(line[j]=='|'){
                    prob2=1;
                    break;
                }
                prob2=0;
            }
            if(prob2!=1){
                char *arg = strtok_r(line, ";", &savePtr1);
                while (arg != NULL){
                    //printf("Current argument: %s\n", arg);
                    char *prog = strtok_r(arg, " ", &savePtr2);
                    if (prog == NULL){
                        continue;
                    }
                    //this is the program, since it is the firt arg
                    args[0] = prog;
                    int counter = 1;
                    args[counter] = NULL;
                    while (prog!= NULL){
                        prog = strtok_r(NULL, " ", &savePtr2);
                        args[counter] = prog;
                        counter++;
                        args[counter] = NULL;
                    }
                    int x = 0;
#ifdef DEBUG
                    for (x = 0; x < counter; x++){
                        printf("Arg[%d]: %s\n", x, args[x]);
                    }
#endif
                    /*
                     * My bash feature for problem 5.
                     * My program emulates bash by allowing a user to enter exit or close to close the prompt.
                     * I took this a step further,by emulating vim by allowing :q to also quit.
                     * To use tis feature, enter exit, quit, or :q when you want to exit ishell.
                     */
                    if ((strcmp(args[0], "exit") == 0) || (strcmp(args[0], "quit") == 0) || (strcmp(args[0], ":q") == 0)){
                        fflush(stdout);
                        printf("Goodbye!\n");
                        free(line);
                        exit (0);
                    }
                    /* Screeshot feature */
                    if (strcmp(args[0], "screenshot") == 0){
                        if (args[1]){
                            if (strcmp(args[1], "-w") == 0){
                                //Whole screen
                                args[0] = "gnome-screenshot";
                                args[1] = "&";
                                args[2] = NULL;
                            }
                        }
                        else{
                            args[0] = "gnome-screenshot";
                            args[1] = "--interactive";
                            args[2] = "&";
                            args[3] = NULL;
                        }
                    }
                    if (strcmp(args[0], "calculator") == 0){
                        args[0] = "gnome-calculator";
                        args[1] = NULL;
                    }
                    forkAndRun(args);
                    arg = strtok_r(NULL, ";", &savePtr1);
                    counter = 0;
                }
            }
            else{
                char *arg1 = strtok(line,"|");
                //printf("%s\n",arg1);
                char *arg2 = strtok(NULL,"|");
                //printf("%s\n",arg2);
                tokenize(arg1,params1);
                tokenize(arg2,params2);
                if(execute(params1,params2)==-1){
                    break;
                }

            }
        }
    }

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

int execute(char** params1,char** params2){
    int pipefd[2];
    pid_t pid1,pid2;
    
    pipe(pipefd);
    pid1 = fork();
    
    if (pid1 == -1){
        perror("first fork\n");
        exit(-1);
    }
    
    if(pid1==0){//child1
        close(1);
        close(pipefd[0]);
        dup2(pipefd[1],1);
        close(pipefd[1]);
        execvp(params1[0],params1);
        perror("first execvp\n");
        return -1;
    }
    
    pid2 = fork();
    if (pid2 == -1){
        perror("second fork\n");
        exit(-1);
    }
    
    if(pid2==0){//child2
        close(0);
        close(pipefd[1]);
        dup2(pipefd[0],0);
        close(pipefd[0]);
        execvp(params2[0],params2);
        perror("second execvp\n");
        return -1;
    }
    
    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);
    printf("[ishell: program termiated successfully]\n");
    return 0;
}

void forkAndRun(char *args[]){
            if (strcmp(args[0],"cd")==0){
                chdir(args[1]);
            }
            else{

			if ((pid = Fork()) == 0){
				//Child process
				//Execute command
				//Have a wrapper, but not calling it since it does perror
				int result = runProgram(args);
				exit(result);

			}
			else{
				//Parent process, wait for child to terminate
				int status;
				Waitpid(-1, &status, 0);
				if (status != 0){
					//Error
					printf("[gshell: process terminated abnormally][%d]\n", status);
				}
				else{
					//No error
					printf("[gshell: process terminated successfully]\n");
				}
            }
            }
}
	
int runProgram(char *args[]){
  print(args);
	int result = Execvp(args[0], args);
	return result;
}
