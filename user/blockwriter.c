#include "kernel/types.h"
#include "user.h"
#include "kernel/fcntl.h"

int main (int argc, char *argv[]){
    int fd;
    char help[] = "-h";
    char help2[] = "--help";
    char output[] = "-o";
    char output2[] = "--output-file";
    char block[] = "-b";
    char block2[] = "--blocks";
    char helpMenu[256];
    int blocks=150;
    char buffer[512];
    char *filename="long.txt";
    strcpy(helpMenu, " Use this program to create a big file filled with a-z characters.\n Default filename: long.txt\n Default blocks: 150\n Usage: blockwriter [OPTION]. . . \n \n Command line options:\n -h, --help:Show help prompt.\n -b, --blocks:Number of blocks to write.\n -o, --output-file: Set output filename.\n");
    int i;
    int result = strcmp(help, argv[1]);
    int result1 = strcmp(help2, argv[1]);
    int result2 = strcmp(output, argv[1]);
    int result3 = strcmp(output2, argv[1]);
    int result4 = strcmp(block, argv[1]);
    int result5 = strcmp(block2, argv[1]);
   
   if(argc==2){
    if(result==0 || result1==0){
      write(1, helpMenu, strlen(helpMenu));
    }else{
		    write(1, "Incorrect command,use -h for help menu\n", 39);
	  }
   }

   if(argc==3){
    if(result2==0 || result3==0){
      filename=argv[2];
      fd = open(filename, O_CREATE | O_WRONLY);
        for(i=0;i<blocks;i++){
          memset(buffer,0,512);
          for (int j = 0; j < 512; j++) {
            buffer[j] = (char)('a' + j % 26); 
            }
          write(fd, buffer, 512);
          printf("Writing block:%d\n", i);
        }
        close(fd);

    }else if(result4==0 || result5==0){
      blocks=atoi(argv[2]);
      fd = open(filename, O_CREATE | O_WRONLY);
        for(i=0;i<blocks;i++){
          memset(buffer,0,512);
          for (int j = 0; j < 512; j++) {
            buffer[j] = (char)('a' + j % 26); 
            }
          write(fd, buffer, 512);
          printf("Writing block:%d\n", i);
        }
        close(fd);
    }else{
		    write(1, "Incorrect command,use -h for help menu\n", 39);
	  }
   }

   if(argc==5){
    if(strcmp(block, argv[1])==0 || strcmp(block2, argv[1])==0 && strcmp(output, argv[3])==0 || strcmp(output2, argv[3])==0){
      blocks=atoi(argv[2]);
      filename=argv[4];
      fd = open(filename, O_CREATE | O_WRONLY);
        for(i=0;i<blocks;i++){
          memset(buffer,0,512);
          for (int j = 0; j < 512; j++) {
            buffer[j] = (char)('a' + j % 26); 
            }
          write(fd, buffer, 512);
          printf("Writing block:%d\n", i);
        }
        close(fd);
    }else if(strcmp(block, argv[3])==0 || strcmp(block2, argv[3])==0 && strcmp(output, argv[1])==0 || strcmp(output2, argv[1])==0){
      blocks=atoi(argv[4]);
      filename=argv[2];
      fd = open(filename, O_CREATE | O_WRONLY);
        for(i=0;i<blocks;i++){
          memset(buffer,0,512);
          for (int j = 0; j < 512; j++) {
            buffer[j] = (char)('a' + j % 26); 
            }
          write(fd, buffer, 512);
          printf("Writing block:%d\n", i);
        }
        close(fd);
    }else{
		    write(1, "Incorrect command,use -h for help menu\n", 39);
	  }
   }
    
    if(argc==1){
      
      fd = open(filename, O_CREATE | O_WRONLY);
        for(i=0;i<blocks;i++){
          memset(buffer,0,512);
          for (int j = 0; j < 512; j++) {
            buffer[j] = (char)('a' + j % 26); 
            }
          write(fd, buffer, 512);
          printf("Writing block:%d\n", i);
        }
        close(fd);
    }
    
    exit();
}