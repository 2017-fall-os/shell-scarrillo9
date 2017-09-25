#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		    /* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		    /* for read */
#include <stdlib.h>		    /* for malloc */
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#include "mytoc.h" 
#define ff fflush(stdout);
#define BUFSIZE 256

int argc;
char **argv;
struct stat buffer;

int main(int argc, char**argv, char **envp){
    int on = 1;
    while(on){
        write(1, "$ ", 2);
        char *input[BUFSIZE] ={0};
		read(0, input, sizeof input);
        
        if(programOff(input)){   //if user inputs exit
			on = 0; break;       //program ends
		}//end if exit
		
		if(input[0] != '\n'){               //if input is not empty, it will go to tokenize and fork
            argv = tokenizeInput(input);    //tokenizing input
            //printf("%s\n", argv[0]);
            
            //checking cmd exists
            if(stat(argv[0], &buffer) == 0 && buffer.st_mode & S_IXOTH){
                int rc = fork();    //forking
                
            
                if(rc < 0){         //forking failed
                    write(0, "fork failed", 11);
                    exit(1);
                }//end if fork failed
            
                else if(rc == 0){   //proceeds to fork
                    if(argc > 1){   //if input is longer than 1 word, contains own path
                        char *path = argv[1];
                        char **pathVector;
                    }
                    else{           //else will use path on envp
                        printf("I am child (pid:%d)\n\n", (int)getpid()); ff;
                    
                        int pathNum = getPath(envp);                            //getting path address
                        char *path = startWord(envp[pathNum], '='); path++;     //path without PATH=
                        //printf("path: %s\n", path); ff;
                        char **pathVector = myToc(path, ':');                   //tokenizing path by :
                        char **temp = pathVector; 
                        for(; temp; temp++){                                    //appends cmd to path
                            char *tempExe = append(*temp, argv[0]);             //and moves to execute
                            printf("%s\n", tempExe); ff;
                            int retVal = execve(tempExe, argv[0], envp);
                            fprintf(stderr, "%s: exec returned %d\n", argv[0], retVal); //if not executed
                        }//end for
                    }//no path specified
                    
                }//end else if fork
            
                else{       //child is killed and then sent to parent
                    int wc = wait(NULL);
                    printf("\nI am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid()); ff;
                }//end else
            }//if command is found
            else{       //didn't find command, prints error
                write(0, "Command not found\n", 19);
            }//else command not found
        }//end if empty
    }//end while on
    return 0;
}//end main

int getPath(char **envp){
    int i =0;
    for(i = 0; envp[i] != (char*)0; i++){
        if(envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
            break;
    }//end for loop
    return i;
}//end getPath

int programOff(char *input){
    char *exit = "exit";
    if(input[0]==exit[0] && input[1]==exit[1] 
        && input[2]==exit[2] && input[3]==exit[3]){
			return 1;
    }//end if exit
    return 0;
}//end program off

char **tokenizeInput(char *input){
    for(int i = 0; input[i] != 0; i++){
        if(input[i] == '\n')
            input[i] = '\0';
    }//end for
    
    char **tokens = myToc(input, ' ');
    argc = getArgc();
        
    //freeVector(tokens);
    //write(1, "after free", 10);
    return tokens;
}//end readInput

