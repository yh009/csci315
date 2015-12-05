/*
 * Ravi Lonberg
 * csci315
 * Lab 12
 */
#include "wrappers.h"
#include <readline/readline.h>
#include <readline/history.h>


int print(char *args[]) {

  if (0!=strcmp(args[0], "print")) {
    return -1;
  } else if ('\0' == args[1]) {
    printf("USAGE: print [filename]\n");
    return -1;
  } else {
  
  pid_t print_pid = Fork();
  int status;

  if (0 == print_pid) { // child process will give list of printers
    printf("\n");
    execlp("/usr/bin/lpstat","/usr/bin/lpstat","-a",(char*) NULL);
  } else { // parent process will ask user to select printer
    Waitpid(print_pid, &status, 0);
    char *printer = readline("\n(^^^) select a given printer: ");

    // execute
    execlp("/usr/bin/a2ps","/usr/bin/a2ps", args[1], "-P", printer, NULL);

  }
  }
  return 0;
}
    

