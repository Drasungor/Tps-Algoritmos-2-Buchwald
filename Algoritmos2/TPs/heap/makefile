CC = gcc
CFLAGS = -g -DCORRECTOR -O2 -std=c99 -Wall -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = heap.c main.c testing.c pruebas_alumnos.c
HFILES = heap.h main.h testing.h
EXEC_S = pruebas


build: $(CFILES)
	$(CC) $(CFLAGS) -o $(EXEC_S) $(CFILES)

run: build
	./$(EXEC_S)

valgrind: build
	valgrind $(VFLAGS) ./$(EXEC_S)

gdb: build
	gdb $(GDBFLAGS) ./$(EXEC_S)

runtime: build
	time ./$(EXEC_S)

clean:
	rm -f *.o $(EXEC_S)
