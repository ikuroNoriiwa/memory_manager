
all: memory_manager

memory_manager: util.o app.o data.o ihm.o main.o
	gcc -o memory_manager util.o app.o data.o ihm.o main.o

main.o: main.c 
	gcc -o main.o -c main.c -W -Wall -ansi -pedantic
 
util.o: util/util.c util/util.h
	gcc -o util.o -c util/util.c -W -Wall -ansi -pedantic

app.o: app/lectureFichier.c app/lectureFichier.h
	gcc -o app.o -c app/lectureFichier.c -W -Wall -ansi -pedantic

data.o: data/data.c
	gcc -o data.o -c data/data.c -W -Wall -ansi -pedantic

ihm.o: ihm/ihm.c
	gcc -o ihm.o -c ihm/ihm.c -W -Wall -ansi -pedantic

clean: 
	rm -rf *.o

recompil: clean
	rm -f memory_manager

