CC=gcc

all: dir_obj main.o io.o lex.o
	$(CC) -o main obj/main.o obj/io.o obj/lex.o

main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o

io.o: src/io.c
	$(CC) -c src/io.c -Iinc -o obj/io.o

lex.o: src/lex.c
	$(CC) -c src/lex.c -Iinc -o obj/lex.o

dir_obj:
	mkdir -p obj

clean:
	rm main
	rm -R obj
