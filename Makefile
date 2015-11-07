FILEPATH=./src/
CFLAGS=-I /usr/local/include -L /usr/local/lib -l gmp

all: RSA

RSA: $(FILEPATH)RSA.o
	gcc $(CFLAGS) $(FILEPATH)RSA.o -o RSA

clean:
	rm $(FILEPATH)*o RSA
