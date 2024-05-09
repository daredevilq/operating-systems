SHELL := /bin/bash

all: compile

compile:
	@gcc -Wall -g -o reader reader.c
	@gcc -Wall -g -o writer writer.c

clean:
	@rm -f reader writer ./myfifo

test: clean
	@chmod +x run_test.sh
	@./run_test.sh

.PHONY: all clean test compile