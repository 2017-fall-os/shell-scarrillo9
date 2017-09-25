#ifndef mytoc_included
#define mytoc_included

//demo method
int numOfWords;

int main(int argc, char**argv, char**envp);

char **myToc(char *str, char delim);

char *copyWord(char *str, int length, char delim);

int countLetters(char *str, char delim);

char *startWord(char *str, char delim);

int countWords(char *str, char delim);

void printVector(char **vector);

void freeVector(char **vector);

void readInput();

int programOff(char *input);

int getPath(char**envp);

int getArgc();

char *append(char *path, char *cmd);
#endif
