/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>

#include "RSA.h" 
#include "miller-rabin.h" 

//Main

int main(int arc, char *argv[]) {
    int prime_size = 512;
    mpz_t p, q, e, m, c;
    public_key k_pu;
    // private_key k_pr;
    private_key_textbook k_pr;

    mpz_init(p);
    mpz_init(q);
    mpz_init(c);
    mpz_init_set_str(m, "427680787658796414495478412765818481773700031964971550032485995462094541318172071699678633526190831000613031464300541848882252073989630802044992230370499993349891121354055409063481101792420859297579606741599372692821291104228771117776673746157967849667351681259816188574800065511460953723930836865732656293632", 10);

    mpz_init_set_ui(e, 65537);

    k_pu = generate_public_key(p, q, e, 512);
    // k_pr = generate_private_key(p, q, e);
    k_pr = generate_private_key_textbook(p, q, e);

    // print_public_key(k_pu);
    // print_private_key_textbook(k_pr);

    printf("%zu\n", mpz_sizeinbase(m, 2));
    printf("%zu\n", mpz_sizeinbase(p, 2));

    gmp_printf("\n%Zd\n", m);

    RSAEP(c, m, k_pu);
    gmp_printf("\n%Zd\n", c);

    RSADP_texbook(m, c, k_pr);
    gmp_printf("\n%Zd\n", m);

    return 0;
}

//Functions

/*
 * Runs the RSA primative RSAEP to encrypt a message using the public key.
 * Parameters:
 *      c - initialized ciphertext value that will be set to the ciphertext of the message m
 *      m - initialized and set message to encrypt
 *      k_pu - public key for RSA
 * Returns:
 *      Ciphertext for a message is returned in the mpz_t s variable.
 */
void RSAEP(mpz_t c,  const mpz_t m, const public_key k_pu) {
    if (mpz_sizeinbase(m, 10) > mpz_sizeinbase(k_pu.n, 10))
        printf("Message representative out of range.\n");

    mpz_powm(c, m, k_pu.e, k_pu.n);
}

/*
 * Runs the RSA primative RSADP to decrypt a message using the private key.
 * Parameters:
 *      m - initialized message to be the return value of the decrypted message
 *      c - initialized and set ciphertext to decrypt
 *      k_pr - private key for RSA texbook
 * Returns:
 *      Plaintext message is returned in the mpz_t value m.
 */
void RSADP_texbook(mpz_t m, const mpz_t c, const private_key_textbook k_pr) {
    if (mpz_sizeinbase(c, 10) > mpz_sizeinbase(k_pr.n, 10))
        printf("Ciphertext representative out of range.\n");
    
    mpz_powm(m, c, k_pr.d, k_pr.n);
}

/*
 * Runs the RSA primative RSADP to decrypt a message using the private key.
 * Parameters:
 *      m - initialized message to be the return value of the decrypted message
 *      c - initialized and set ciphertext to decrypt
 *      k_pr - private key for RSA using CRT
 * Returns:
 *      Plaintext message is returned in the mpz_t value m.
 */
void RSADP(mpz_t m, const mpz_t c, const private_key k_pr) {
    mpz_t n, m_1, m_2, h, h_1, h_2, h_3;
    mpz_init(n);
    mpz_init(m_1);
    mpz_init(m_2);
    mpz_init(h);
    mpz_init(h_1);
    mpz_init(h_2);
    mpz_init(h_3);

    mpz_mul(n, k_pr.q, k_pr.p);

    if (mpz_sizeinbase(c, 10) > mpz_sizeinbase(n, 10))
        printf("Ciphertext representative out of range.\n");

    
    mpz_powm(m_1, c, k_pr.dP, k_pr.p);
    mpz_powm(m_2, c, k_pr.dQ, k_pr.q);

    mpz_sub(h_1, m_1, m_2);
    mpz_powm_ui(h_2, k_pr.qInv, 1, k_pr.p);
    mpz_mul(h, h_1, h_2);

    mpz_mul(h_3, k_pr.q, h);
    mpz_add(m, m_2, h_3);
}
