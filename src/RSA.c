/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "miller-rabin.h" 

//Struct Definitions

//Struct representation of a public key used for asynchronous cryptography
typedef struct public_key {
    mpz_t n; //RSA modulus, a positive integer.
    mpz_t e; //RSA public exponent, a positive integer.
} public_key;

//Function Prototypes

public_key set_public_key(const char *str_n, const char *str_e);
void generate_prime(mpz_t p, int prime_size);

int main(int arc, char *argv[]) {
    mpz_t p;
    generate_prime(p, 512);

    gmp_printf("Prime = %Zd\n", p);
    return 0;
}

/*
 * Creates a public key used for asymmetric cryptography.
 * Parameters:
 *      str_n - string value representing n, the RSA modulus
 *      str_e - string value resprsenting e, the RSA private exponent
 * Returns:
 *      k_pu - struct representation of the RSA public key
 */
public_key set_public_key(const char *str_n, const char *str_e) {
    public_key k_pu;

    //Initialize values of the public key to 0.
    mpz_init(k_pu.n);
    mpz_init(k_pu.e);

    //Assign str_* to * of the public key in base 10;
    mpz_set_str(k_pu.n, str_n, 10);
    mpz_set_str(k_pu.e, str_e, 10);

    return(k_pu);
}

/*
 * Creates a prime number using the Miller-Rabin primality test.
 * Parameters:
 *      p - empty value for p, generate_prime saves its value to this variable
 *          p represents a large prime number to be used with RSA's n = pq
 *      prime_size - size of prime in bits, 512 is typical for an RSA modulus of 1024 bits
 * Returns:
 *      p - the input parameter p is also where this function stores the value returned
 */
void generate_prime(mpz_t p, int prime_size) {
    mpz_t max, two;

    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui (rand_state, time(NULL));

    mpz_init(max);
    mpz_init_set_ui(two, 2);
    mpz_mul_2exp(max, two, prime_size + 1);
    mpz_init(p);

    do {
        mpz_urandomm(p, rand_state, max);
        if (mpz_even_p(p)) continue;
        if (mpz_fdiv_ui(p, 3) == 0) continue;
        if (mpz_fdiv_ui(p, 5) == 0) continue;
        if (mpz_fdiv_ui(p, 7) == 0) continue;
    } while (miller_rabin(p, rand_state) == COMPOSITE);
}
