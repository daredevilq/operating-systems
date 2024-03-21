# !!! UWAGA (paczka zostala wyslana z przykladowym plikiem raportu _zad2.txt) !!!
# w celu sprawdzenia poprawnosci wykonania cwiczenia nalezy najpierw wykonac:
# make clean -> zeby upewnic sie ze nie ma zbednych plikow
# make all -> polecenie generuje odpowidni raport do pliku _zad2.txt
# tylko te dwa polecenia sa potrzebne do sprawdzenia poprawonosci dzialania rozwiazania


CC = gcc
CFLAGS = -Wall -std=c17
#liczba plikow ktore zostana wygenerowane w katalogu test-directory
NUMBER_OF_FILES = 5

.PHONY: all clean


all:
	make raport
	make generate_directory
	make size_sum
	make raport_check


size_sum: size_sum.c generate_files
	$(CC) $(CFLAGS) -o size_sum size_sum.c
	./size_sum

# target tworzy katalog test-directory oraz generuje i wypelnia NUMBER_OF_FILES plikow, stala jest zdefiniowana u gory makefile,
# ilosc bajtow w plikach jest generowana losowo, nie przekazujemy ilosci bajtow
generate_directory:
	mkdir test-directory
	$(CC) $(CFLAGS) -o generate_files generate_files.c
	./generate_files $(NUMBER_OF_FILES)

# tworzy plik raportu i dodaje komentarze, dane zapisywane sa w funkcji main pliku size_sum.c
raport:
	touch _zad2.txt
	@echo "Raport zadania 2" >> _zad2.txt
	@echo "" >> _zad2.txt
	@echo "Wyniki dla size_sum.c:" >> _zad2.txt


# wpisuje do pliku rozmiary plikow za pomoca polecenia ls 
raport_check: _zad2.txt
	@echo "" >> _zad2.txt
	@echo "Sprawdzenie wynikow komenda ls:" >> _zad2.txt
	ls -l test-directory >> _zad2.txt 

clean:
	rm -r test-directory
	rm size_sum
	rm _zad2.txt
	rm generate_files


# ls -l |awk '{printf "-%5s %-s\n", $5, $9}'