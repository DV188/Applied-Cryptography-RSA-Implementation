/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#ifndef RSA_H
#define RSA_H

#include <gmp.h>

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
    mpz_t qInv; //(first) CRT exponent, positive integer.
} private_key;

//Function Prototypes

public_key set_public_key(const mpz_t n, const mpz_t e);
private_key set_private_key(const mpz_t p, const mpz_t q, const mpz_t dP, const mpz_t dQ, const mpz_t qInv);

void print_public_key(public_key k_pu);
void print_private_key(private_key k_pr);

void generate_prime(mpz_t p, int prime_size);
int validate_e(const mpz_t e, mpz_t p, mpz_t q, int prime_size);
int multiplicative_inverse(mpz_t result, const mpz_t exponent, const mpz_t prime);

public_key generate_public_key(mpz_t p, mpz_t q, const mpz_t e, int prime_size);
private_key generate_private_key(const mpz_t p, const mpz_t q, const mpz_t e);

void RSAEP(mpz_t c, const mpz_t m, const public_key k_pu);
void RSADP(mpz_t m, const mpz_t c, const private_key k_pr);

#endif
