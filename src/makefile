client_dynamic: main.o myfilefunctions.o mystrfunctions.o
	gcc main.o -lmyutils -lc -L../lib -o ../bin/client_dynamic
myfilefunctions.o: myfilefunctions.c 
	gcc -c myfilefunctions.c
mystrfunctions.o: mystrfunctions.c 
	gcc -c mystrfunctions.c
main.o: main.c
	gcc -c main.c
