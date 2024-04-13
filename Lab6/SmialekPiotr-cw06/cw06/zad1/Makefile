.PHONY: all clean test

CC = gcc
CFLAGS = -Wall -std=c17


integral: integral.c
	$(CC) $(CFLAGS) -o integral integral.c -lm

test: integral
	@echo "Wyniki testow:"
	@echo ""
	@echo "Interval width: 0.01 ; processes: 100"
	./integral 0.01 100
	@echo ""
	@echo "Interval width: 0.001 ; processes: 1000"
	./integral 0.001 1000
	@echo ""
	@echo "Interval width: 0.0001 ; processes: 1000"
	./integral 0.0001 1000
	@echo ""
	@echo "Interval width: 0.00001 ; processes: 1000"
	./integral 0.00001 1000
	@echo ""
	@echo "Interval width: 0.000001 ; processes: 1000"
	./integral 0.000001 1000
	@echo ""
	@echo "Interval width: 0.0000001 ; processes: 1000"
	./integral 0.0000001 1000
	@echo ""
	@echo "Interval width: 0.00000001 ; processes: 1000"
	./integral 0.00000001 1000
	@echo ""
	@echo "Interval width: 0.000000001 ; processes: 1000"
	./integral 0.000000001 1000
	@echo ""

clean:
	rm integral