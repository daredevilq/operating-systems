CC = gcc
CFALGS = -std=c11 -Wall 


all: server.c client.c
	$(CC) $(CFALGS) -o server server.c
	$(CC) $(CFALGS) -o client client.c

server: server.c
	$(CC) $(CFALGS) -o server server.c

client: client.c
	$(CC) $(CFALGS) -o client client.c

test_server: all
	./server 127.0.0.1 8888

test_client1: all
	./client 1 127.0.0.1 8888

test_client2: all
	./client 2 127.0.0.1 8888

clean: 
	rm -f client server

