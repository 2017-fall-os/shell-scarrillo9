all: run

run: tokenizer.o shell1.o
	cc -o $@ $^
	
shell1.o: shell1.c mytoc.h
	cc -c $(CFLAGS) shell1.c
	
tokenizer.o: tokenizer.c mytoc.h
	cc -c $(CFLAGS) tokenizer.c
	
clean: 
	rm -f *.o run

demo: run
	./run
