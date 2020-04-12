CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes

CFILES = pruebas_alumno.c main.c testing.c main.c
HFILES = vector_dinamico.h testing.h
EXEC_S = pruebas
PADRON = 12345


#SEGUIR EL MAKE, INVESTIGAR Y ESTUDIAR COMANDOS


build: *c
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

zip:
	zip $(PADRON).zip $(CFILES) $(HFILES)

entregar: build
	$(MAKE) run; test $$? -eq 0
	$(MAKE) valgrind; test $$? -eq 0
	$(MAKE) clean
	zip $(PADRON).zip $(CFILES) $(HFILES)
	@echo "Perfecto, no falla ni pierde memoria"
	@echo "El zip esta listo para entregar"
