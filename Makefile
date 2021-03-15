test : lib.o 
	gcc lib.o libs/libtest.c -o libtest.exe
	rm lib.o
lib.o : libs/lib.c
	gcc -c libs/lib.c
