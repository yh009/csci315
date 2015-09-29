//Yuxuan Huang
//csci315 prelab2

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char* argv[]){
    int pid;
    
    char *test = (char*)malloc(13*sizeof(char));
    strcpy(test,"testingonly");
    printf("in parent\ntestingonly\n");
    if ((pid = fork()) == 0) {
        printf("in child\n%s\n",test);
        return 0;
    }
    else{
        return 0;
    }
}
