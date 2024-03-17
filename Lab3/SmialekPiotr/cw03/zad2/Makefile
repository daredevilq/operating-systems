# w celu sprawdzenia poprawnosci wykonania cwiczenia nalezy najpierw wykonac:
# make clean -> zeby upewnic sie ze nie ma zbednych plikow
# make all -> polecenie generuje odpowidni raport 


CC = gcc
CFLAGS = -Wall -std=c17


.PHONY: all clean


all:
	make generate_directory
	make generate_data
	make size_sum


size_sum: size_sum.c
	$(CC) $(CFLAGS) -o size_sum size_sum.c
	./size_sum

generate_directory:
	mkdir test-directory
	touch ./test-directory/file1.txt
	touch ./test-directory/file2.txt
	touch ./test-directory/file3.txt

generate_data:
	@echo "asdasdasdasdasdasdasdaspodasdasdasdajsfods" >> ./test-directory/file1.txt
	@echo "asdasdasdasdasdasdasdaspodasdasdasdadasdasdajsfods" >> ./test-directory/file2.txt
	@echo "asdasdasdasdasdasdasdas12321podasdasczxczxczxczxczxdasdajsfods" >> ./test-directory/file3.txt

clean:
	rm ./test-directory/file1.txt
	rm ./test-directory/file3.txt
	rm ./test-directory/file2.txt
	rmdir test-directory
	rm size_sum