CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99 -gstabs -lncurses
LDFLAGS=
EXEC=memory_manager


all: $(EXEC)

memory_manager: util.o app.o data.o ihm.o main.o
	$(CC) -o $(EXEC) util.o app-*.o data.o ihm.o main.o $(CFLAGS)

main.o: main.c 
	$(CC) -o main.o -c main.c $(CFLAGS)
 
util.o: util/util.c util/util.h
	$(CC) -o util.o -c util/util.c $(CFLAGS)

app.o: app/lectureFichierMemory.c app/lectureFichierMemory.h
	rm -rf app-*.o
	$(CC) -o app-lectureFichierMemory.o -c app/lectureFichierMemory.c $(CFLAGS)
	$(CC) -o app-lectureFichierProcess.o -c app/lectureFichierProcess.c $(CFLAGS)
	$(CC) -o app-lectureFichierCPU.o -c app/lectureFichierCPU.c $(CFLAGS) 

data.o: data/data.c
	$(CC) -o data.o -c data/data.c $(CFLAGS)

ihm.o: ihm/ihm.c
	$(CC) -o ihm.o -c ihm/ihm.c $(CFLAGS)

clean: 
	rm -rf *.o

recompil: clean
	rm -f memory_manager

