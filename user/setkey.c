#include "kernel/types.h"
#include "user.h"

int isdigit(int c) {
    return c >= '0' && c <= '9';
}

int is_number(char* str) {
    int i = 0;
    int sign_count = 0;
    int decimal_count = 0;

    // Skip optional sign at the beginning
    if (str[i] == '+' || str[i] == '-') {
        sign_count++;
        i++;
    }

    // Check each character in the string
    while (str[i] != '\0') { 
        if (isdigit(str[i])) {
            // If character is a digit, continue
            i++;
        } else if (str[i] == '.') {
            // If character is a decimal point, continue
            decimal_count++;

            // If more than one decimal point found, not a number
            if (decimal_count > 1) {
                return 0;
            }
    i++;
        } else {
            // If character is neither a digit nor a decimal point, not a number
            return 0;
        }
    }
        // If at least one digit is present, consider it as a number
    if (i > 0 && (sign_count <= 1) && (decimal_count <= 1)) {
        return 1;
    } else {
        return 0;
    }
}

int main (int argc, char *argv[]){
    char help[] = "-h";
    char help2[] = "--help";
    char secret[] = "--secret";
    char secret2[] = "-s";
    char helpMenu[256];
    char key[10];
    int shiftKey;
    strcpy(helpMenu, "Use this program to set the current active key.\n After setting the key, you can use encr and decr with that key.\n Usage: setkey [OPTION]. . . [KEY]\n \n Command line options: \n -h, --help: Show help promt. \n -s, --secret: Enter the key via STDIN. Hide key when entering it.\n");
    int result = strcmp(help, argv[1]);
    int result1 = strcmp(help2, argv[1]);
    int result2 = strcmp(secret, argv[1]);
    int result3 = strcmp(secret2, argv[1]);


if(argc==2){
    if(result==0 || result1==0){
      write(1, helpMenu, strlen(helpMenu));
    }else if(result2==0 || result3==0){
        write(1, "Enter the key:", 15);
        setecho(1);
        read(0,key,10);
        shiftKey = atoi(key);
        setecho(0);
        if(setkey(shiftKey)<0){
            write(1, "Key not set\n", 13);
    }
    }else if(is_number(argv[1])==0){
        write(1, "Invalid argument.\n Use -h for help menu.\n", 41);
    }else{
    shiftKey=atoi(argv[1]);
    setkey(shiftKey);
    }
}

    
    exit();
}