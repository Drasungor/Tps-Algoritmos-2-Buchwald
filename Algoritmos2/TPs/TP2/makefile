CC = gcc
CFLAGS = -g -DCORRECTOR -O2 -std=c99 -Wall -Wtype-limits -pedantic -Wconversion -Wno-sign-conversion -Wbad-function-cast -Wshadow -Wpointer-arith -Wunreachable-code -Wformat=2 -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = algueiza.c strutil.c abb.c hash.c vuelo.c lista.c pila.c contador.c heap.c auxiliares.c
HFILES = strutil.h abb.h hash.h vuelo.h lista.h pila.h contador.h heap.h auxiliares.h algueiza.h
EXEC_S = algueiza


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
