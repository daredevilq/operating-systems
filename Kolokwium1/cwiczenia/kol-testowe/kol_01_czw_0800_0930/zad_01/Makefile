
all:
	mkdir lib
	mkdir bin
	LD_LIBRARY_PATH=./lib
	gcc -fPIC -c bibl1.c
	mv bibl1.o ./bin
	gcc -o ./lib/bibl1.so ./bin/bibl1.o -shared
	gcc zad1.c -o zad1 -ldl

clean:
	rm -f ./lib/bibl1.so
	rm -f ./bin/bibl1.o
	rmdir lib
	rmdir bin