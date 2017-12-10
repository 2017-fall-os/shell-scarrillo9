#include <stdio.h>  
#include <stdlib.h> 
#include <sys/types.h>		/* for lseek, read */
#include <unistd.h>		    /* for lseek, read */
#include <sys/stat.h>		/* for read */
#include <fcntl.h>		    /* for read */
#include <sys/wait.h>

#include "mytoc.h" 
#define ff fflush(stdout);

int numOfWords = 0;

char **myToc(char *str, char delim){
	numOfWords = countWords(str, delim);
	//creating pointer array
	char **vector = (char **)calloc(numOfWords+1, sizeof(char *));
	vector[numOfWords] = '\0';	//creating null value at end of array
	char *currString = str;
	int i;
    
	for(i = 0; i < numOfWords; i++){
		int wordLength = countLetters(currString, delim);	//gets length of first word
		vector[i] = copyWord(currString, wordLength, delim);	//copy the word in the nextor space allocated
        char *currWord = startWord(currString, delim);      //gets the new string without the word just allocated
		currString = currWord;
	}//end for loop
	//printVector(vector);
	return vector;
}//end myToc

//frees vector
void freeVector(char **vector){
    char **temp = vector;
	for(; vector; vector++){
		free(*vector);
	}//end for loop
	//numOfWords = 0;
	free(temp);
    printVector(vector);
}//end freeVector

//prints vector created
void printVector(char **vector){
	int i;
	for(i = 0; i < numOfWords; i++){
		char *currVec = vector[i];
		printf("\nWord #%d: ", i+1); ff;
		while(*currVec != '\0'){
			printf("%c", *currVec); ff;
			currVec++;
		}//end while
	}//end for loop
	printf("\n"); ff;
}//end printVector

//copies the word into the allocated memory
char *copyWord(char *str, int length, char delim){
	//printf("inside copyWord\n"); ff;
	char *currArray = (char *)malloc(length+1);
	currArray[length] = '\0';
	
	int i;
	int j = 0;
	for(i = 0; i < length; i++){
		if(str[j] == delim){
			j++; i--;
		}
		else{
			currArray[i] = str[j];
			j++;
		}
	}//end for loop
	
	return currArray;
}//end copyWord

//counts the letters in a word
int countLetters(char *str, char delim){
	int count = 0;
	
	while(*str != '\0'){
		if(*str == delim && count == 0){
			str++;
		}//end if string hasn't seen word
		if(*str == delim && count > 0){
			break;
		}//end if comes across a space after word
		if(*str != delim){
			count++;
			str++;
		}//end if counting word
	}//end while
	
	//printf("inside countLetters %d\n", count); ff;
	return count;
}//end countLetters

//cuts the first word of the string off
char *startWord(char *str, char delim){
	//printf("inside startWord\n"); ff;
	char *newstr = str;
	int onWord = 0;
	
	while(*newstr != '\0'){
		if(*newstr == delim && onWord == 0)
			newstr++; 
		if(*newstr == delim && onWord == 1)
			break;
		if(*newstr != delim && onWord == 0){
			onWord = 1;
			newstr++;
		}
		if(*newstr != delim && onWord == 1)
			newstr++;
	}//end while
	
	return newstr;
}//end wordLength

//counts the amount of words in a string
int countWords(char *str, char delim){
	int i = 0; 
	int numOfWords = 0;
	int space = 1;	//multiple delims

	while(str[i] != '\0'){
		if(str[i] != delim && space == 1){
			numOfWords++;
		}//end if
		if(str[i] == delim){
			space = 1;
		}//end if
		else
			space = 0;
		i++;
	}//end while
	//printf("inside countWords %d\n", numOfWords); ff;
	
	return numOfWords;
}//end countWords

char *append(char *path, char *cmd){
    int pathn = countLetters(path, ' ');
    int cmdn = countLetters(cmd, ' ');
    int length = pathn + cmdn;
    
    char *curr = (char *)malloc(length+2);
	curr[length] = '\0';
	
	int i;
	for(i = 0; i < pathn; i++){
        curr[i] = path[i];
	}//end for loop
	curr[i] = '/'; i++;
	int j;
	for(j = 0; j < cmdn; j++){
        curr[i] = cmd[j];
        i++;
    }//end for
    return curr;
}//end append

int isDelim(char *input, char delim){
    int i;
    for(i = 0; input[i] != 0; i++){
        if(input[i] == delim)
            return 1;
    }//end for
    return 0;
}//end ifPipe

int getPathLocation(char **envp){
    int i;
    for(i = 0; envp[i] != (char*)0; i++){
        if(envp[i][0] == 'P' && envp[i][1] == 'A' 
            && envp[i][2] == 'T' && envp[i][3] == 'H'){
            break;
        }
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

int changeDirectory(char *input){
    char *dirchange = "cd";
    if(input[0]==dirchange[0] && input[1]==dirchange[1]){
        return 1;
    }//end if exit
    return 0;
}//end program off

char *getPath(char **envp){
    int pathNum = getPathLocation(envp);
    char *path = startWord(envp[pathNum], '='); 
    path++;
    return path;
}//end getpath

char *fixInput(char *input){
    for(int i = 0; input[i] != 0; i++){
        if(input[i] == '\n')
            input[i] = '\0';
    }//end for
    
    return input;
}//end fixInput

int piping(char *input, char **envp){
    char **pipes = myToc(input, '|');
    char *path = getPath(envp); 
    int *thisPipe;
    thisPipe = (int *)calloc(2, sizeof(int));
    
    //printf("pipe 1: %s\npipe 2: %s\n", pipes[0], pipes[1]); ff;
    pipe(thisPipe);

    int rc = fork();
    
    if(rc == 0){
        wait(NULL);
        close(1);
        dup(thisPipe[1]);
        close(thisPipe[0]); 
        close(thisPipe[1]);
        execveConditions(pipes[0], path, envp);
        exit(2);
    }//end if pipe
    else{
        close(0);
        dup(thisPipe[0]);
        close(thisPipe[1]);
        close(thisPipe[0]);
        execveConditions(pipes[1], path, envp);
    }//end else
    return 0;
}//end piping

void execveConditions(char *command, char *path, char **envp){
    char **currCom = myToc(command, ' ');
    //if(numOfWords > 1){
      //  char *path = currCom[1];
        //int retVal = execve(path, currCom, envp);
  //  }//end if path is specified
    
    //else{
        if(command[0] == '/' || command[1] == '/'){
            int retVal = execve(currCom[0], currCom, envp);
        } else{
            char **pathVector = myToc(path, ':');
            char **temp = pathVector;
            for(; temp; temp++){
                char *tempExe = append(*temp, currCom[0]);
                int retVal = execve(tempExe, currCom, envp);
            }//end for loop
        }//end else
    //}//end else
    freeVector(currCom);
}//end conditions


int getStringSize(char *input){
    int count = 0;
    for(; input; input++){
        count++;
    }//end for
    printf("%d\n", count);
    return count;
}//end getStringSize
