

.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -std=c17

all: signal_demonstrator.c
	$(CC) $(CFLAGS) -o signal_demonstrator signal_demonstrator.c

test: all
	@echo "none->"
	./signal_demonstrator none || echo "Failed to execute 'none'"
	@echo ""
	@echo "handler->"
	./signal_demonstrator handler || echo "Failed to execute 'handler'"
	@echo ""
	@echo "mask->"
	./signal_demonstrator mask || echo "Failed to execute 'mask'"
	@echo ""
	@echo "ignore->"
	./signal_demonstrator ignore || echo "Failed to execute 'ignore'"


clean:
	rm -f signal_demonstrator