#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		/* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		/* for read */
#include <stdlib.h>		/* for malloc */
#include <stdio.h>

#include "mytoc.h" 

#define BUFSIZE 256

int main(){
	readInput();
	
	//char **tokens = myToc("   hey what's your   name", ' ');
	
	//freeVector(tokens);
    return 0;
}//end main

int programOff(char *input){
    char *exit = "exit";
    if(input[0]==exit[0] && input[1]==exit[1] && input[2]==exit[2] && input[3]==exit[3]){
			return 1;
    }//end if exit
    return 0;
}//end program off

void readInput(){
	int on = 1;
    //char *input[BUFSIZE];
    
	while(on){
        char *input[BUFSIZE]= {0};
		write(1, "$ ", 2);
		read(0, input, sizeof input);
        
        for(int i = 0; input[i] != 0; i++){
            if(input[i] == '\n')
                input[i] = '\0';
        }//end for
		
		if(programOff(input)){
			on = 0; break;
		}//end if exit
		
		char **tokens = myToc(input, ' ');
		
		//char **tokens = myToc("   hey what's your   name", ' ');
		//freeVector(tokens);
        write(1, "after free", 10);
	}//end while on
}//end readInput
