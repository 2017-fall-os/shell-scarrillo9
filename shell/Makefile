all: shell

shell: tokenizer.o shell.o
	cc -o $@ $^
	
shell.o: shell.c mytoc.h
	cc -c $(CFLAGS) test.c
	
tokenizer.o: tokenizer.c mytoc.h
	cc -c $(CFLAGS) mytoc.c
	
clean: 
	rm -f *.o mytoc

demo: run
	./run
