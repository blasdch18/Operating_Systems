

	gcc -c main.c -o main.o


	gcc -c factorial.c -o static/factorial.o


	gcc -c answer.c -o static/answer.o


	gcc -c -fPIC factorial.c -o dynamic/factorial.o


	gcc -c -fPIC answer.c -o dynamic/answer.o



	ar rcs static/libucsp2.a static/factorial.o static/answer.o


	gcc main.o -Lstatic/ -lucsp -o statically-linked.exe


	
	gcc -shared dynamic/factorial.o dynamic/answer.o -o dynamic/libucsp2.so


	gcc main.o -Lshared/ -lucsp -o shared-library.exe


	rm -f factorial.o answer.o main.o


	
