CC = gcc
CFLAGS = -Wall -std=c17 


.PHONY: all static_build shared_build clean

all:
	make static_build
	make shared_build

static_build: collatz.c
	$(CC) $(CFLAGS) -o static_build -c collatz.c
	ar rcs libstatic_build.a static_build



# Flaga -fPIC włącza generowanie „kodu niezależnego od pozycji”, co jest wymogiem dla bibliotek 
# dynamicznych. Flaga -c konwertuje natomiast pliki .c na pliki obiektów (.o).
shared_build: collatz.c
	$(CC) $(CFLAGS) -fPIC -o shared_build.o -c collatz.c 
	$(CC) $(CFLAGS) -shared -o libshared_build.so shared_build.o

clean:
	rm -f *.so *.a *.o static_build