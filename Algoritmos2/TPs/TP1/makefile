CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes



CFILES_DC = operaciones.c pila.c dc.c strutil.c
HFILES_DC = operaciones.h pila.h  strutil.h
EXEC_S_DC = dc

CFILES_GREP = grep.c lista.c strutil.c
HFILES_GREP = lista.h strutil.h
EXEC_S_GREP = grep

CFILES_PRUEBA_STRUTIL = strutil.c prueba_strutil.c
HFILES_PRUEBA_STRUTIL = strutil.h
EXEC_S_PRUEBA_STRUTIL = strutil


build_strutil: $(CFILES_PRUEBA_STRUTIL)
	$(CC) $(CFLAGS) -o $(EXEC_S_PRUEBA_STRUTIL) $(CFILES_PRUEBA_STRUTIL)

build_dc: $(CFILES_DC)
	$(CC) $(CFLAGS) -o $(EXEC_S_DC) $(CFILES_DC)

run_dc: build_dc
	./$(EXEC_S_DC)

valgrind_dc: build_dc
	valgrind $(VFLAGS) ./$(EXEC_S_DC)

gdb_dc: build_dc
	gdb $(GDBFLAGS) ./$(EXEC_S_DC)

build_grep: $(CFILES_GREP)
	$(CC) $(CFLAGS) -o $(EXEC_S_GREP) $(CFILES_GREP)

run_grep: build_grep
	./$(EXEC_S_GREP)

valgrind_grep: build_grep
	valgrind $(VFLAGS) ./$(EXEC_S_GREP)

gdb_grep: build_GREP
	gdb $(GDBFLAGS) ./$(EXEC_S_GREP)


runtime: build_dc
	time ./$(EXEC_S_DC)

clean:
	rm -f *.o $(EXEC_S_DC)

zip:
	zip $(PADRON).zip $(CFILES) $(HFILES)
