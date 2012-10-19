CC=clang++
CFLAGS=-Wall -g
LDFLAGS=-lgmpxx -lgmp

all: ail

ail: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) obj/* -o bin/ail
	/usr/local/bin/doxygen doxygen.conf

main.o: element.o context.o parser.o tokenizer.o
	$(CC) $(CFLAGS) -c src/main.cc -o obj/main.o

element.o:
	$(CC) $(CFLAGS) -c src/element.cc -o obj/element.o

context.o: element.o
	$(CC) $(CFLAGS) -c src/context.cc -o obj/context.o

tokenizer.o:
	$(CC) $(CFLAGS) -c src/tokenizer.cc -o obj/tokenizer.o

parser.o: context.o tokenizer.o
	$(CC) $(CFLAGS) -c src/parser.cc -o obj/parser.o

clean:
		rm -f obj/*
		rm -rf bin/*
		rm -rf docs/*
