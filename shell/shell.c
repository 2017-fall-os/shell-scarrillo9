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


int main(int argc, char **argv, char **envp){
    int rc = fork();
    
    if(rc < 0){
        write(0, "fork failed", 11);
        exit(1);
    }//end if fork failed
    
    else if(rc == 0){
        printf("I am child (pid:%d)\n", (int)getpid()); ff;
        
        char *cmd = "ls";
        int pathNum = getPath(envp);
        char *path = startWord(envp[pathNum], '='); path++;
        //printf("path: %s\n", path); ff;
        char **pathVector = myToc(path, ':');
        char **temp = pathVector;
        for(; temp; temp++){
            char *tempExe = append(*temp, cmd);
            printf("%s\n", tempExe); ff;
            //int retVal = execve(tempExe, cmd);
            //fprintf(stderr, "%s: exec returned %d\n", argv[0], retVal);
        }//end while
    }//end else if fork
    
    else{
        int wc = wait(NULL);
        printf("I am parent of %d (wc:%d) (pid:%d)\n", rc, wc, (int)getpid()); ff;
    }//end else
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

