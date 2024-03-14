# W celu sprawdzenia poprawnosci dzialania odpowiedniej biblioteki trzeba uzyc jednego z ponizszych polecen:
# make test_static
# make test_shared
# make test_dynamic
# uzycie jednego z powyzszych polecen spowoduje powstanie pliku z wynikiem do ktorego mozemy sie dostac za pomoca ./output

# pozbywamy sie wszystkich zbednych plikow za pomoca make clean


CC = gcc
CFLAGS = -Wall -std=c17


.PHONY: all static_build shared_build clean test_static test_shared test_dynamic

all:
	make static_build
	make shared_build

static_build: collatz.c
	$(CC) $(CFLAGS) -c collatz.c
	ar rcs libstatic.a collatz.o


# Flaga -fPIC włącza generowanie „kodu niezależnego od pozycji”, co jest wymogiem dla bibliotek 
# dynamicznych. Flaga -c konwertuje natomiast pliki .c na pliki obiektów (.o).
shared_build: collatz.c
	$(CC) $(CFLAGS) -fPIC -c collatz.c 
	$(CC) $(CFLAGS) -o libshared.so collatz.o -shared

test_static: client.c
	make static_build
	$(CC) $(CFLAGS) -c client.c
	$(CC) $(CFLAGS) client.o libstatic.a -o output
	@echo "output wygenerowany za pomoca biblioteki statycznej"

test_shared: client.c
	make shared_build
	$(CC) $(CFLAGS) client.c -o output -lshared -L. -Wl,-rpath=./
	@echo "output wygenerowany za pomoca biblioteki wspoldzielonej"

test_dynamic: client.c
	$(CC) $(CFLAGS) -fPIC -c collatz.c 
	$(CC) $(CFLAGS) -o libdynamic.so collatz.o -shared
	$(CC) $(CFLAGS) -o output client.c -ldl -D DYNAMIC

clean:
	rm -f *.so *.a *.o output