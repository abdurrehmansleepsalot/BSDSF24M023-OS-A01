client: main.o myfilefunctions.o mystrfunctions.o
	gcc main.o -lmyutil -lc -L../lib -o ../bin/client_static
myfilefunctions.o: myfilefunctions.c 
	gcc -c myfilefunctions.c
mystrfunctions.o: mystrfunctions.c 
	gcc -c mystrfunctions.c
main.o: main.c
	gcc -c main.c
