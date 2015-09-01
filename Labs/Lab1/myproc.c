/*Yuxuan H/Volumes/linux-yh009.$/csci315/Labs/Lab1/myproc.cuang
  csci315 prelab1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    int p;
    int c1;
    int c2;
    int p_next=1;
    int c1_next=1;
    int c2_next=1;
    
    while (1){
        p = p_next;
        p_next++;
        
        
        printf("parent:%i\n",p);
        while(1){
            c1 = c1_next;
            c1_next++;
            
            printf("child1:%i\n",c1);
            break;
        }
        while(1){
            c2 = c2_next;
            c2_next++;
            
            printf("child2:%i\n",c2);
            break;
        }
    }
}

