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

int main(int argc, char **argv, char **envp){
    int on = 1;
    
    while(on){
        write(1, "$ ", 2);
        char input[BUFSIZE] ={0};
		read(0, input, sizeof input);
        
        if(programOff(input)){   //if user inputs exit
			on = 0; break;      //program ends
			exit(1);
		}//end if exit
		
		
		if(input[0] != '\n'){               //if input is not empty, it will go to tokenize and fork
            if(isPipe(input)){
                char **pipeCommand = myToc(input, '|');
                int pathNum = getPath(envp);    //getting path address
                char *path = startWord(envp[pathNum], '='); path++; 
                piping(pipeCommand, path, envp);
            }//end isPipe
            else{
            argv = tokenizeInput(input);    //tokenizing input
            
            if(changeDirectory(argv[0])){
                int retVal = chdir(argv[1]);
            }//end to chdir
            
            int rc = fork();    //forking   
            
            if(rc < 0){         //forking failed
                write(0, "fork failed", 11);
                
                exit(1);
            }//end if fork failed
            
            else if(rc == 0){   //proceeds to fork
                if(argc > 1){   //if input is longer than 1 word, contains own path
                    char *path = argv[1];
                    int retVal = execve(path, argv, envp);
                    //fprintf(stderr, "%s: exec returned %d\n", argv[0], retVal);
                }//if path is specified
                
                else{           //else will use path on envp
                    if(input[0] == '/'){
                        int retVal = execve(argv[0], argv, envp);
                        //fprintf(stderr, "%s: exec returned %d\n", argv[0], retVal);
                    }//end if path specified
                    
                    else{
                    //printf("I am child (pid:%d)\n\n", (int)getpid()); ff;
                
                        int pathNum = getPath(envp);                            //getting path address
                        char *path = startWord(envp[pathNum], '='); path++;     //path without PATH=
                        //printf("path: %s\n", path); ff;
                        char **pathVector = myToc(path, ':');                   //tokenizing path by :
                        char **temp = pathVector; 
                        for(; temp; temp++){                                    //appends cmd to path
                            char *tempExe = append(*temp, argv[0]);             //and moves to execute
                            //printf("%s\n", tempExe); ff;
                            int retVal = execve(tempExe, argv, envp);
                            //fprintf(stderr, "%s: exec returned %d\n", argv[0], retVal); //if not executed
                        }//end for
                    }//end else to use PATH
                }//more than one word command
            }//end else if fork
            
            else{       //child is killed and then sent to parent
                int wc = wait(NULL);
                //printf("\nI am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid()); ff;
            }//end else
            }
        }//end if empty
    }//end while on
    return 0;
}//end main

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

