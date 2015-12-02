//Yuxuan Huang
//Lab11
//Problem 4

#include <stdio.h>
#include <stdlib.h>

int main(){
    char buf[1024];
    FILE *write = fopen("channel.txt","w");
    fclose(write);//in case channel.txt doesnt exist
    FILE *receive = fopen("channel.txt", "r");
    while(1){
        if(fgets(buf,sizeof(buf),receive)!=NULL){
            printf("receiver [msg arrival]: %s\n",buf);
            fflush(stdout);
        }
    }
}