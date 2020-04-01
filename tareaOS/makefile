


main.o:	main.c
	gcc -c main.c -o main.o

factorial.o: factorial.c
	gcc -c factorial.c -o static/factorial.o

static/answer.o: answer.c
	gcc -c answer.c -o static/answer.o

dynamic/factorial.o: factorial.c
	gcc -c -fPIC factorial.c -o dynamic/factorial.o

dynamic/answer.o: answer.c
	gcc -c -fPIC answer.c -o dynamic/answer.o


libucsp.a: static/factorial.o static/answer.o 
	ar rcs static/libucsp.a static/factorial.o static/answer.o

statically-linked.exe: main.o
	gcc main.o -Lstatic/ -lucsp -o statically-linked.exe


libucsp.so: factorial.o answer.o	
	gcc -shared dynamic/factorial.o dynamic/answer.o -o dynamic/libucsp.so

shared-library.exe: main.o
	gcc main.o -Lshared/ -lucsp -o shared-library.exe

clean:
	rm -f factorial.o answer.o main.o


	
