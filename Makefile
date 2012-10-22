CC=clang++
CFLAGS=-Wall -g
LDFLAGS=-lgmpxx -lgmp

all: ail

ail: main.o
	$(CC) $(CFLAGS) $(LDFLAGS) obj/* -o bin/ail

main.o: element.o context.o parser.o tokenizer.o
	$(CC) $(CFLAGS) -c src/main.cc -o obj/main.o

element.o:
	$(CC) $(CFLAGS) -c src/Element.cc -o obj/element.o

symbol_element.o:
	$(CC) $(CFLAGS) -c src/SymbolElement.cc -o obj/symbol_element.o

native_symbol_element.o: symbol_element.o
	$(CC) $(CFLAGS) -c src/NativeSymbolElement.cc -o obj/native_symbol_element.o

definition_symbol_element.o: symbol_element.o
	$(CC) $(CFLAGS) -c src/DefinitionSymbolElement.cc -o obj/definition_symbol_element.o

string_element.o:
	$(CC) $(CFLAGS) -c src/StringElement.cc -o obj/string_element.o

number_element.o: string_element.o
	$(CC) $(CFLAGS) -c src/NumberElement.cc -o obj/number_element.o

context.o: element.o native_symbol_element.o definition_symbol_element.o number_element.o
	$(CC) $(CFLAGS) -c src/Context.cc -o obj/context.o

tokenizer.o:
	$(CC) $(CFLAGS) -c src/Tokenizer.cc -o obj/tokenizer.o

operators.o:
	$(CC) $(CFLAGS) -c src/Operators.cc -o obj/operators.o

parser.o: context.o tokenizer.o operators.o
	$(CC) $(CFLAGS) -c src/Parser.cc -o obj/parser.o

clean:
		rm -f obj/*
		rm -rf bin/*
		rm -rf docs/*
