//Yuxuan Huang
//csci315
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/statvfs.h>


int main(int argc, char *argv[]){
  char name;
  struct statvfs buf;
  name =  argv[1];
  int fd = fopen(name,"w+");
  fstatvfs(fd,&buf);
  int block_size = (int)(buf.f_blocks);
  unsigned long max_name = buf.f_namemax;
  printf("block size: %d\n",block_size);
  printf("max filename: %lu\n",max_name);
  return 0;
}
