# W celu sprawdzenia poprawnosci dzialania programów nalezy:
# make clean -> zeby pozbyc sie niechianych plikow
# make test -> zeby przetestowac program, po uruchomieniu make test nalezy wprowadzic dwie liczby:
# pierwsza jest poczatek interwalu a drugm koniec interwalu na ktorym liczona jest calka (poaczatek < koniec)
# po wprowadzniu tych dwoch liczb (po wprowadzeniu kazdej wscikamy ENTER) powinnien wyswietlisc sie wynik w konsoli obliczonej calki

.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -std=c17


test: integral_manager compute_integral
	./compute_integral &
	./integral_manager


manager: integral_manager.c
	$(CC) -o integral_manager integral_manager.c

compute: compute_integral.c
	$(CC) -o compute_integral compute_integral.c


clean:
	rm *.fifo integral_manager compute_integral
