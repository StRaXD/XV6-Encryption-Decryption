#include "kernel/types.h"
#include "user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "kernel/fs.h"

  char *files[100];
  int w = 0;

char*
fmtname(char *path)
{
	static char buf[DIRSIZ+1];
	char *p;

	// Find first character after last slash.
	for(p=path+strlen(path); p >= path && *p != '/'; p--)
		;
	p++;

	// Return blank-padded name.
	if(strlen(p) >= DIRSIZ)
		return p;
	memmove(buf, p, strlen(p));
	memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
	return buf;
}

void
ls(char *path)
{
	char buf[512], *p;
	int fd;
	struct dirent de;
	struct stat st;

	if((fd = open(path, 0)) < 0){
		fprintf(2, "ls: cannot open %s\n", path);
		return;
	}

	if(fstat(fd, &st) < 0){
		fprintf(2, "ls: cannot stat %s\n", path);
		close(fd);
		return;
	}

	switch(st.type){
	case T_FILE:
		printf("%s %d %d %d\n", fmtname(path), st.type, st.ino, st.size);
		break;
  case T_DIR:
		if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
			printf("ls: path too long\n");
			break;
		}
		strcpy(buf, path);
		p = buf+strlen(buf);
		*p++ = '/';
		while(read(fd, &de, sizeof(de)) == sizeof(de)){
			if(de.inum == 0)
				continue;
			memmove(p, de.name, DIRSIZ);
			p[DIRSIZ] = 0;
			if(stat(buf, &st) < 0){
				printf("ls: cannot stat %s\n", buf);
				continue;
			}
      if(st.type==T_FILE){
      files[w] = (char*) malloc(strlen(de.name) + 1);
      strcpy(files[w], de.name);
      w++;
     // printf("%s", de.name);
      }
			
		}
		break;
  }
	close(fd);
}


int main (int argc, char *argv[]){
    char help[] = "-h";
	char help2[] = "--help";
    char all[] = "-a";
	char all2[] = "--encrypt-all";
    char helpMenu[256];
    strcpy(helpMenu, "\n Use this program to encrypt files written on the disk.\n Usage: encr [OPTION]. . . [FILE]. . . \n \n Command line options: \n -h, --help: Show help prompt. \n -a, --encrypt-all: Ecrypt all files in CWD with current key. \n");
    int fd;
    int result = strcmp(help, argv[1]);
	int result1 = strcmp(help2, argv[1]);
    int result2 = strcmp(all, argv[1]);
	int result3 = strcmp(all2, argv[1]);
    char *filename;
    
   if(argc==2){
    if(result==0 || result1==0){
      write(1, helpMenu, strlen(helpMenu));
    }else if(result2==0 || result3==0){
     ls(".");
      for (int j = 0; j < w; j++) {
        filename=files[j];
      	fd = open(filename, O_RDWR);
		int odgovor = encrypt(fd);
		 if(odgovor==-1){
          	printf("Failed to encrypt file %s [key not set]\n",filename);
          }else if(odgovor==-2){
			printf("Failed to encrypt file %s [file is T_DEV type]\n",filename);
		  }else if(odgovor==-3){
			printf("Failed to encrypt file %s [file already encrypted]\n",filename);
		  }else{
			printf("Successfully encrypted file %s\n", filename);
		  }
        free(files[j]);
    }
    }
    else{
      filename=argv[1];
	  fd = open(filename, O_RDWR);
	  if(fd!=-1){
	  int odgovor = encrypt(fd);
        if(odgovor==-1){
          	printf("Key not set\n");
          }else if(odgovor==-2){
			printf("Can't encrypt T_DEV file\n");
		  }else if(odgovor==-3){
			printf("File %s already encrypted\n", filename);
		  }else{
			printf("Successfully encrypted file %s\n", filename);
		  }
	  }else{
		    write(1, "Incorrect command,use -h for help menu\n", 39);
	  }
    }
   }
   
    exit();
}