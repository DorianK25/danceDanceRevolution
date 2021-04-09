install: lib.o
	gcc lib.o script.c -o dance.exe
	rm lib.o
uninstall:
	rm dance.exe
test : lib.o 
	gcc lib.o libs/libtest.c -o  libtest.exe -lncurses
	rm lib.o
lib.o : libs/lib.c
	gcc -c libs/lib.c -lncurses
