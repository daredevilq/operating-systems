CC=gcc
BUILD_DIR=build
BUILD := debug
CFLAGS := -std=c11 -Wall

ifeq ($(BUILD),debug)
    CFLAGS += -g -O0
else
    CFLAGS += -O2
endif

.PHONY: all clean

all: client server

client: client.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<

server: server.c
	rm -rf /dev/mqueue/*
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<

run_client: client 
	./$(BUILD_DIR)/client

run_server: server
	./$(BUILD_DIR)/server
	
clean:
	rm -f /dev/mqueue/*
	rm -rf $(BUILD_DIR)
