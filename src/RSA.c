/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <gmp.h> //GNU Multiple Precision Arithmetic Library(https://gmplib.org/), used for big numbers.

//Struct Definitions

//Struct representation of a public key used for asynchronous cryptography
typedef struct public_key {
    mpz_t n; //RSA modulus, a positive integer.
    mpz_t e; //RSA public exponent, a positive integer.
} public_key;

//Function Prototypes

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

int main(int arc, char *argv[]) {
    public_key k_pu = set_public_key("123", "456");

    gmp_printf("n = %Zd, e = %Zd\n", k_pu.n, k_pu.e);

    return(0);
}
