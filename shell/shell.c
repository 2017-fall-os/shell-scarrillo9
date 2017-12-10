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

int main(int argc, char **argv, char **envp){
    int on = 1;
   // char *PS1 = getenv("PS1");
    
    while(on){
        
        if(getenv("PS1")){
            char *PS1 = getenv("PS1");
            int PS1length = getStringSize(PS1);
            write(1, getenv("PS1"), PS1length);
        }//end if ps1
        else{
            write(1, "$ ", 2);
        }
        
        char input[BUFSIZE];
		int lengthRead = read(0, input, sizeof input);
        if(lengthRead == 1){
            on = 1;
            continue;
        }
        
        input[lengthRead-1] = '\0';
        
        if(programOff(input)){   //if user inputs exit
			on = 0; break;      //program ends
			exit(1);
		}//end if exit
		
		argv = myToc(input, ' ');         //tokenizing input
        argc = countWords(input, ' ');
        char *path = getPath(envp);
        
		if(input[0] != '\n'){               
            //if input is not empty, it will go to tokenize and fork
            if(argv == NULL){
                continue;
            }
            
            if(isDelim(input, '&')){ //check if background task
                int rc = fork();    //forking
                if(rc == 0){
                    input[lengthRead-2] = '\0';
                    execveConditions(input, path, envp);
                }//end background
                else{
                    wait(NULL);
                }
            }//end isBackground
            
            if(isDelim(input, '|')){ //checks if pipe
                int rc = fork();    //forking   
            
                if(rc == 0){
                    int retVal = piping(input, envp);
                }//end if pipeCommand
                else{
                    wait(NULL);
                }//end else
            }//end isPipe
            
            if(changeDirectory(argv[0])){ //checks if cd
                //printf("here at chdir\n"); ff;
                int retVal = chdir(argv[1]);
                
                if(retVal < 0){
                    perror("error"); 
                }
                
                wait(NULL);
            }//end to chdir
            
            
            else{
                //printf("here at beginning\n"); ff;
                
                int rc = fork();    //forking   
            
                if(rc < 0){         //forking failed
                    write(0, "fork failed", 11);
                    exit(1);
                }//end if fork failed
                
                
                else if(rc == 0){   //proceeds to fork
                    if(argc > 1){   
                        //if input is longer than 1 word, contains own path
                        char *path = argv[1];
                        int retVal = execve(path, argv, envp);
                    }//if path is specified
                
                    else{           
                        //else will use path on envp
                        if(input[0] != '/'){
                            char **pathVector = myToc(path, ':');       //tokenizing path by :
                            char **temp = pathVector;   
                            for(; temp; temp++){                        //appends cmd to path
                                char *tempExe = append(*temp, argv[0]); //and moves to execute
                                int retVal = execve(tempExe, argv, envp);
                            }//end for
                            //freeVector(pathVector);
                        }//end if path specified
                        else{
                            int retVal = execve(argv[0], argv, envp);
                        }//end else to use PATH
                    }//more than one word command
                }//end else if fork
                else{
                    wait(NULL);
                }
            }//end else runs commands
        }//end if empty
    }//end while on
    return 0;
}//end main

