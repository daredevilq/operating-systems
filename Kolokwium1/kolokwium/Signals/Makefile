CC=gcc
CFLAGS=-Wall -g
TARGET=signals

SIGUSR1 := $(shell kill -l SIGUSR1)
SIGUSR2 := $(shell kill -l SIGUSR2)
SIGHUP := $(shell kill -l SIGHUP)
SIGALRM := $(shell kill -l SIGALRM)

all: $(TARGET)

$(TARGET): $(TARGET).o
	$(CC) $(CFLAGS) -o $@ $^

$(TARGET).o: $(TARGET).c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(TARGET) $(TARGET).o

test: test_valid_signals test_invalid_args test_invalid_signals test_non_numeric_value

test_valid_signals:
	@echo "Test 1: Sending SIGUSR1 with value 123"
	-@./$(TARGET) 123 $(SIGUSR1) && echo "\033[0;32mSuccess: Valid test passed.\033[0m" || echo "\033[0;31mFail: Valid test failed.\033[0m"
	@echo "Test 2: Sending SIGUSR2 with value 456"
	-@./$(TARGET) 456 $(SIGUSR2) && echo "\033[0;32mSuccess: Valid test passed.\033[0m" || echo "\033[0;31mFail: Valid test failed.\033[0m"

test_invalid_args:
	@echo "Test 3: Invalid number of arguments"
	-@./$(TARGET) 123 ; if [ $$? -eq 1 ]; then echo "\033[0;32mSuccess: Handled invalid argument count.\033[0m"; else echo "\033[0;31mFail: Did not handle invalid argument count.\033[0m"; fi

test_invalid_signals:
	@echo "Test 4: Sending a non-handled signal (SIGHUP)"
	-@./$(TARGET) 789 $(SIGHUP) | grep -q "was not handled by the child" && echo "\033[0;32mSuccess: Correctly rejected non-handled signal.\033[0m" || echo "\033[0;31mFail: Incorrectly accepted non-handled signal.\033[0m"
	@echo "Test 5: Sending another non-handled signal (SIGALRM)"
	-@./$(TARGET) 101 $(SIGALRM) | grep -q "was not handled by the child" && echo "\033[0;32mSuccess: Correctly rejected non-handled signal.\033[0m" || echo "\033[0;31mFail: Incorrectly accepted non-handled signal.\033[0m"

test_non_numeric_value:
	@echo "Test 6: Sending SIGUSR1 with non-numeric value 'abc'"
	-@./$(TARGET) abc $(SIGUSR1) 2>&1 | grep -q "Both arguments must be numeric" && echo "\033[0;32mSuccess: Correctly rejected non-numeric value.\033[0m" || echo "\033[0;31mFail: Incorrectly accepted non-numeric value.\033[0m"
