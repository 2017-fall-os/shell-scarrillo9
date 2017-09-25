#include <stdio.h>  
#include <stdlib.h> 

#include "mytoc.h" 
#define ff fflush(stdout);

int numOfWords = 0;

char **myToc(char *str, char delim){
	//printf("inside myToc\n"); ff;
	numOfWords = countWords(str, delim);
	
	//creating pointer array
	char **vector = (char **)calloc(numOfWords+1, sizeof(char *));
	vector[numOfWords] = NULL;	//creating null value at end of array
	char *currString = str;
	
	int i;
	for(i = 0; i < numOfWords; i++){
		int wordLength = countLetters(currString, delim);	//gets length of first word
		
		vector[i] = (char *)malloc(sizeof(char)*wordLength+1);	//allocates the memory needed
		vector[wordLength] = NULL;	//creates null value to end array
		vector[i] = copyWord(currString, wordLength, delim);	//copy the word in the nextor space allocated
		
		char *currWord = startWord(currString, delim);	//gets the new string without the word just allocated
		
		//printf("currString: %s\n currWord: %s\n", currString, currWord); ff;
		currString = currWord;
	}//end for loop
	//printVector(vector);
	return vector;
}//end myToc

int getArgc(){
    return numOfWords;
}//end getArgc

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
