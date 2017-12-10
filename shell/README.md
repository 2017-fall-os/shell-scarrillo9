# Operating Systems Lab 2 - Shell
# Stefany Carrillo

This directory contains:
* code that implements a shell for user input

The demo program reads input from the user.
The string is first tokenized and checked to see that it is not empty. If it's not empty it will go ahead and check if the command was given by itself or with a path. If given by itself it will get the envp path and append the command to all the directories in the path and try to execute them. Will return an error if execution fails.

This demo contains the following files:
 * mytoc.h: header file of the methods shared between the 2 c files.
 * tokenizer.c: implementation of the tokenizer; where all the functions dealing with tokenizing are located.
 * shell.c: a demonstration program that uses the shell with a couple helper functions.

To compile:
~~~
$ make all
~~~

To test it, try:
~~~
$ ./run
~~~

To delete binaries:
~~~
$ make clean
~~~

Talked and troubleshooted with Ricardo Alvarez and Ana Garcia on the execution of commands for part 1, and showed Ricardo how my change directory command worked. Used Freudenthal's demo code for piping. Used code from book on forking. Received help from Ricardo on the PS1 script testing. 

09/12/17 - Problem with the '$ ' prompt. Background tasks, pipes, change directory, and regular commands work. When testing the script, all tests failed. The initial prompt is probably the problem.
