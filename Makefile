FILEPATH=./src/
CFLAGS=-I /usr/local/include -L /usr/local/lib -l gmp

all: RSA

RSA: $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o $(FILEPATH)key_generation.o $(FILEPATH)test.o
	gcc $(CFLAGS) $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o $(FILEPATH)key_generation.o $(FILEPATH)test.o -o RSA

RSA.o: $(FILEPATH)RSA.c
	gcc -c $(FILEPATH) RAS.c

key_generation.o: $(FILEPATH)key_generation.c
	gcc -c $(FILEPATH) key_generation.c

miller-rabin.o: $(FILEPATH)miller-rabin.c
	gcc -c $(FILEPATH) miller-rabin.c

test.o: $(FILEPATH)test.c
	gcc -c $(FILEPATH) test.c

clean:
	rm -v $(FILEPATH)*o RSA
