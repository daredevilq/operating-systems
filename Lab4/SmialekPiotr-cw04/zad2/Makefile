# W celu sprawdzenia poprawności działania programu nalezy:
# 1. Wykonać make clean -> żeby upewnić się ze nie ma niepotrzebnych plików
# 2. Wykonać make test -> stworzy to odpowiedni folder w folderze bierzącym i 
# dla tego folderu zostanie wykonany program
# można także wykonać make all i wstedy zostanie tylko skompilowany program i # bedziemy mogli podać własny argument: np. ./main . -> co sprawdzi bieżący # folder


.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -std=c17



all:
	gcc -o main main.c

test: 
	mkdir test-directory
	touch test-directory/file1.txt
	touch test-directory/file2.txt
	gcc -o main main.c
	./main test-directory

clean:
	rm main
	rm -r test-directory