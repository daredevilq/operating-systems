#!!! UWAGA (paczka zostala wyslana z przykladowym plikiem raportu _zad1.txt) !!!
# Do sprawdzania zadania trzeba wykonac kolejno:
# make clean -> zeby upewnic sie ze wszystkie niepotrzebne pliki zostana wyczyszone 
# make all -> komenda wykonuje szereg czynnosci i tworzy nam raport w postaci pliku _zad1.txt, 
# w ktorym znajduja sie szczegoly, wszystkie czynnosci beda wykonane za nas wystarczy wykonanie tych dwoch komend 
# i sprawdzenie raportu w pliku _zad1.txt

# output_file.txt jest odwroconym plikiem input_file.txt
# temp_file.txt jest odwroconym plikiem output_file.txt czyli w teorii powinien byc taki sam jak plik input_file.txt

.PHONY: all clean generate 

CC = gcc
CFLAGS = -Wall -std=c17
FILE_SIZE = 100000

all:
	make generate
	make reverse
	@echo >> _zad1.txt
	@echo "" >> _zad1.txt
	@echo "Wynik komendy diff -s input_file.txt temp_file.txt :" >> _zad1.txt
	diff -s input_file.txt temp_file.txt >> _zad1.txt
	

generate: generate_file.c
	$(CC) $(CFLAGS) -o generate generate_file.c
	./generate $(FILE_SIZE)

reverse: reverse.c
	$(CC) $(CFLAGS) -o reverse reverse.c
	./reverse
	rm reverse
	$(CC) $(CFLAGS) -o reverse reverse.c -D BLOCK
	./reverse

clean2:
	rm reverse generate input_file.txt output_file.txt temp_file.txt

clean: 
	rm *.txt reverse generate





