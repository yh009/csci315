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
#include "print.h"

pid_t pid; //process ids

void forkAndRun(char *args[]);
int runProgram(char *args[]);

int main(int argc, char *argv[]){
	char *line = malloc(sizeof(char)*50);
	size_t len = 0;
	char *savePtr1, *savePtr2; //used in thread safe tokenizer
	int inNewLineBool = 0;; //used to detect two newline hits
    char cwd[100];
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
	}
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
				/*
				if (result == -1){
					printf("[ishell: program terminated abnormally][%d]", errno); 
				}
				else{
					printf("\n[ishell: program terminated successfully]\n");
				}
				exit(0);
				*/
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
