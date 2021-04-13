install: lib_functions.o
	gcc lib_functions.o main.c -o dance.exe -lncurses
	rm lib_functions.o
uninstall:
	rm dance.exe
test : lib_functions.o 
	gcc lib_functions.o librairies/libtest.c -o  libtest.exe -lncurses
	rm lib.o
lib.o : librairies/lib_functions.c
	gcc -c librairies/lib_functions.c -lncurses
