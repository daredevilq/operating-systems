CC = gcc
CFLAGS = -Wall -std=c17

.PHONY: all

all: countdown


# target (countdown) can be replaced with $@ -> $(CC) $(CFLAGS) countdown.c -o $@
# first prerequisite can be replaced with $< 
# all prerequisites can be replaced with $^
# -g flag is used to include debugging information in the executable file
# gdb countdown -> layout next -> run  -> break main -> (next, step, continue, print i, display, info, list, quit, help, etc.)
countdown: 
	$(CC) $(CFLAGS) countdown.c -o countdown -g

.PHONY: clean
clean:
	rm -f *.o countdown


#Without linking:

# .PHONY: all
# all: countdown
# countdown: countdown.o
# 	gcc countdown.o -o countdown
# countdown.o: countdown.c
# 	gcc -c countdown.c
# .PHONY: clean
# clean:
# 	rm -f *.o countdown