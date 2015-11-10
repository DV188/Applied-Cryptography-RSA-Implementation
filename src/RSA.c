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

#define exponent_e

//Struct Definitions

//Struct representation of a public key used for asynchronous cryptography
typedef struct public_key {
    mpz_t n; //RSA modulus, a positive integer.
    mpz_t e; //RSA public exponent, a positive integer.
} public_key;

//Struct representation of a private key used for asynchronous cryptography
//Chinese Remainder Theorem is used.
typedef struct private_key {
    mpz_t p; //First factor, a positive integer.
    mpz_t q; //Second factor, a positive integer.
    mpz_t dP; //First factor CRT exponent, positive integer.
    mpz_t dQ; //Second factor CRT exponent, positive integer.
    mpz_t dInv; //(first) CRT exponent, positive integer.
} private_key;

//Function Prototypes

public_key set_public_key(mpz_t n, mpz_t e);
void print_public_key(public_key k_pu);
void generate_prime(mpz_t p, int prime_size);
int validate_e(mpz_t p, mpz_t q, int prime_size);
int multiplicative_inverse(mpz_t result, mpz_t exponent, mpz_t pq_minus_1);

//Main

int main(int arc, char *argv[]) {
    int prime_size = 512;
    mpz_t e, p, q, n, dP;
    public_key k_pu;

    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(dP);

    mpz_init_set_ui(e, 65537);

    generate_prime(p, prime_size);
    generate_prime(q, prime_size);

    mpz_mul(n, p, q);

    k_pu = set_public_key(n, e);

    gmp_printf("p = %Zd, q = %Zd\n", p, q);

    validate_e(p, q, prime_size);

    print_public_key(k_pu);

    int rc = multiplicative_inverse(dP, e, p - 1);

    gmp_printf("%d: %Zd\n", rc, dP);

    return 0;
}

//Functions

/*
 * Creates a public key used for asymmetric cryptography.
 * Parameters:
 *      str_n - string value representing n, the RSA modulus
 *      str_e - string value resprsenting e, the RSA private exponent
 * Returns:
 *      k_pu - struct representation of the RSA public key
 */
public_key set_public_key(mpz_t n, mpz_t e) {
    public_key k_pu;

    //Initialize values of the public key to 0.
    mpz_init(k_pu.n);
    mpz_init(k_pu.e);

    //Assign str_* to * of the public key in base 10;
    mpz_set(k_pu.n, n);
    mpz_set(k_pu.e, e);

    return(k_pu);
}

/*
 * Prints the public key to std out.
 * Parameters:
 *      k_pu - struct public_key representing the public key
 */
void print_public_key(public_key k_pu) {
    gmp_printf("Public Key: (%Zd, %Zd)\n", k_pu.n, k_pu.e);
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

/*
 * Validation of e must be performed to make sure our primes have been created correctly.
 * Parameters:
 *      p - prime number generated randomly
 *      q - prime number generated randomly
 *      prime_size - size of the prime in bits, must be the same as p and q
 * Returns:
 *      Returns 1 if function completes.
 *      If p and q do not properly validate, p and q will be changed.
 */
int validate_e(mpz_t p, mpz_t q, int prime_size) {
    mpz_t e;
    mpz_t gcd;
    mpz_t lcm;

    mpz_init(gcd);
    mpz_init(lcm);

    mpz_init_set_ui(e, 65537);

    mpz_lcm(lcm, p, q);
    mpz_gcd(gcd, e, lcm);

    while (mpz_get_ui(gcd) != 1) {
        generate_prime(p, prime_size);
        generate_prime(q, prime_size);

        mpz_lcm(lcm, p - 1, q - 1);
        mpz_gcd(gcd, e, lcm);

        printf("Generating new primes.\n");
    }

    return(1);
}

/*
 * Computes the multiplicative inverse of a private key.
 * Parameters:
 *      result - where the result is stored
 *      exponent - public key exponent
 *      pq_minus_1 - the value of prime p - 1
 * Returns:
 *      Returns 0 if functions cannot be inverted.
 */
int multiplicative_inverse(mpz_t result, mpz_t exponent, mpz_t pq_minus_1) {
    return(mpz_invert(result, exponent, pq_minus_1));
}
