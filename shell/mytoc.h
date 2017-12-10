#ifndef mytoc_included
#define mytoc_included

//shell.c
int main(int argc, char**argv, char**envp);

int programOff(char *input);

int changeDirectory(char *input);

char *getPath(char**envp);

int getPathLocation(char **envp);

char **tokenizeInput();


//tokenizer.c
char **myToc(char *str, char delim);

char *copyWord(char *str, int length, char delim);

int countLetters(char *str, char delim);

char *startWord(char *str, char delim);

int countWords(char *str, char delim);

void printVector(char **vector);

void freeVector(char **vector);

char *append(char *path, char *cmd);

int changeDirectory(char *input);

int isDelim(char *input, char delim);

int piping(char *input, char **envp);

void execveConditions(char *command, char *path, char **envp);

int getStringSize(char *input);

char *fixInput(char *input);

#endif
