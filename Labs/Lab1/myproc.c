/*Yuxuan Huang
  csci315 prelab1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(){
  pid_t child1;
  pid_t child2;
  int p=1;
  int c1=1;
  int c2=1;

  child1=fork();
  if(child1!=0){
    child2=fork();
      }
    
    while (1){
      if (child1!=0 && child2!=0){
	printf("parent:%i\n",p);
        p++;
      }
      else{
	if(child1==0){
	  printf("child1:%i\n",c1);
	  c1++;
	}
	else if(child2==0){
	    printf("child2:%i\n",c2);
	    c2++;
	  }
      }
    }
}     


