# w celu sprawdzenia poprawności programu należy:
# 1. W pierwszej kolejności wukonać make clean -> # żeby upewnić się że nie ma niepotrzebnych plików
# 2.Wykonać make test która stworzy nam 20 procesów
# Ewentualnie można wykonać make all i podać własna ilość procesów np. ./main 100


.PHONY: all clean test 

CC = gcc
CFLAGS = -Wall -std=c17


all:
	$(CC) $(CFLAGS) -o main main.c

test:
	$(CC) $(CFLAGS) -o main main.c
	./main 20

clean:
	rm main
