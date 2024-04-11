# W celu sprawdzenia poprawności działania programu nalezy:
# 1. Wykonać make clean -> żeby upewnić się ze nie ma niepotrzebnych plików
# 2. Wykonać make all -> polecenie skompiluje dwa pliki sender.c i catcher.c
# 3. Nalezy odpalic dwa terminale w swoim systemie
# 4. Najpierw nalezy wywlolac w jednym terminalu  ./catcher ktory uruchomi program ktory bedzie oczekiwal na sygnal
# 5. Nastepnie nalezy wywolac w drugum terminalu ./sender <catcher PID> <operating mode 1, 2 albo 3> (<catcher PID> wyswietli sie w terminalu w ktorym wywolalismy ./catcher, nalezy go przepisac)


.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -std=c17

all: sender catcher

sender: sender.c
	$(CC) $(CFLAGS) -o sender sender.c


catcher: catcher.c
	$(CC) $(CFLAGS) -o catcher catcher.c


clean:
	rm catcher sender