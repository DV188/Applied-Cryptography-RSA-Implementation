FILEPATH=./src/
CFLAGS=-I /usr/local/include -L /usr/local/lib -l gmp

all: main

main: $(FILEPATH)main.o $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o $(FILEPATH)key_generation.o $(FILEPATH)data_conversion_primatives.o $(FILEPATH)oaep.o
	gcc $(CFLAGS) $(FILEPATH)main.o $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o $(FILEPATH)key_generation.o $(FILEPATH)data_conversion_primatives.o $(FILEPATH)oaep.o -o RSA

main.o: $(FILEPATH)main.c
	gcc -c $(FILEPATH) main.c

RSA.o: $(FILEPATH)RSA.c
	gcc -c $(FILEPATH) RSA.c

oaep.o: $(FILEPATH)oaep.c
	gcc -c $(FILEPATH) oaep.c

data_conversion_primatives.o: $(FILEPATH)data_conversion_primatives.c
	gcc -c $(FILEPATH) data_conversion_primatives.c

key_generation.o: $(FILEPATH)key_generation.c
	gcc -c $(FILEPATH) key_generation.c

miller-rabin.o: $(FILEPATH)miller-rabin.c
	gcc -c $(FILEPATH) miller-rabin.c

clean:
	rm -v $(FILEPATH)*o RSA
