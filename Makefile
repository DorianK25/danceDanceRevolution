install: lib.o
	gcc lib.o script.c -o dance.exe
	rm lib.o
lib.o: libs/lib.c
	gcc -c libs/lib.c

uninstall:
	rm dance.exe