#ifndef mytoc_included
#define mytoc_included

//shell.c
int main(int argc, char**argv, char**envp);

int programOff(char *input);

int getPath(char**envp);

char **tokenizeInput();


//tokenizer.c
char **myToc(char *str, char delim);

char *copyWord(char *str, int length, char delim);

int getArgc();

int countLetters(char *str, char delim);

char *startWord(char *str, char delim);

int countWords(char *str, char delim);

void printVector(char **vector);

void freeVector(char **vector);

char *append(char *path, char *cmd);

#endif
