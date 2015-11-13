/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#ifndef KEY_GENERATION_H
#define KEY_GENERATION_H

#include <gmp.h>

//Struct Definitions

//Struct representation of a public key used for asynchronous cryptography
typedef struct public_key {
    mpz_t n; //RSA modulus, a positive integer.
    mpz_t e; //RSA public exponent, a positive integer.
} public_key;

//Struct representation of a private key used for asynchronous cryptography
//Texbook RSA is used.
typedef struct private_key_textbook {
    mpz_t n; //RSA modulous, a positive integer.
    mpz_t d; //RSA private exponent, a positive integer.
} private_key_textbook;

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
private_key_textbook set_private_key_texbook(const mpz_t n, const mpz_t d);
private_key set_private_key(const mpz_t p, const mpz_t q, const mpz_t dP, const mpz_t dQ, const mpz_t qInv);

void print_public_key(public_key k_pu);
void print_private_key_textbook(private_key_textbook k_pr);
void print_private_key(private_key k_pr);

public_key generate_public_key(mpz_t p, mpz_t q, const mpz_t e, int prime_size);
private_key_textbook generate_private_key_textbook(const mpz_t p, const mpz_t q, const mpz_t e);
private_key generate_private_key(const mpz_t p, const mpz_t q, const mpz_t e);

void generate_prime(mpz_t p, int prime_size);
int validate_e(const mpz_t e, mpz_t p, mpz_t q, int prime_size);

#endif
