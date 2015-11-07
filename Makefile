FILEPATH=./src/
CFLAGS=-I /usr/local/include -L /usr/local/lib -l gmp

all: RSA

RSA: $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o
	gcc $(CFLAGS) $(FILEPATH)RSA.o $(FILEPATH)miller-rabin.o -o RSA

RSA.o: $(FILEPATH)RSA.c
	gcc -c $(FILEPATH) RAS.c

miller-rabin.o: $(FILEPATH)miller-rabin.c
	gcc -c $(FILEPATH) miller-rabin.c

clean:
	rm -v $(FILEPATH)*o RSA
