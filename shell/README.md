# Operating Systems Lab 1 - Tokenizer
# Stefany Carrillo

This directory contains:
* code that implements a tokenizer for a string input
* a demo program that uses it

The demo program reads input from the user.
The string is first checked to see the amount of words. Once the tokenizer knows the amount of words, it allocates memory for the amount of words and then checks the lengths of the words to later allocate the memory space for the letters in the words.

This demo contains the following files:
 * mytoc.h: header file of the methods shared between the 2 c files.
 * mytoc.c: implementation of the tokenizer; where all the functions are located.
 * test.c: a demonstration program that uses the tokenizer and frees the memory allocated.

To compile:
~~~
$ make all
~~~

To test it, try:
~~~
$ ./mytoc
~~~

To delete binaries:
~~~
$ make clean
~~~

I received help/guidance from Ricardo Alvarez and Ana Garcia on how to implement the memory allocation for the letters after allocating the word space.