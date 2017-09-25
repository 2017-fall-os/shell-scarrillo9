all: run

run: tokenizer.o shell.o
	cc -o $@ $^
	
shell.o: shell.c mytoc.h
	cc -c $(CFLAGS) shell.c
	
tokenizer.o: tokenizer.c mytoc.h
	cc -c $(CFLAGS) tokenizer.c
	
clean: 
	rm -f *.o run

demo: run
	./run
