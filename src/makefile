client_dynamic: main.o myfilefunctions.o mystrfunctions.o
	gcc main.o -lmyutils -lc -L../lib -o ../bin/client_dynamic
myfilefunctions.o: myfilefunctions.c 
	gcc -c myfilefunctions.c
mystrfunctions.o: mystrfunctions.c 
	gcc -c mystrfunctions.c
main.o: main.c
	gcc -c main.c
install: client_dynamic
	@echo "Installing 'client' executable to /usr/local/bin"
	install -d /usr/local/bin
	install -m 755 ../bin/client_dynamic /usr/local/bin/client
	@echo "Installing shared library to /usr/local/lib"
	install -d /usr/local/lib
	install -m 755 ../lib/libmyutils.so /usr/local/lib/
	ldconfig
	@echo "Installing 'mycat' man page to /usr/local/share/man/man1"
	install -d /usr/local/share/man/man1
	install -m 644 ../man/man1/mycat.1 /usr/local/share/man/man1/mycat.1
