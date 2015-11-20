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
    if (mpz_sizeinbase(m, 2) > mpz_sizeinbase(k_pu.n, 2))
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
    if (mpz_sizeinbase(c, 2) > mpz_sizeinbase(k_pr.n, 2))
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

    if (mpz_sizeinbase(c, 2) > mpz_sizeinbase(n, 2))
        printf("Ciphertext representative out of range.\n");

    
    mpz_powm(m_1, c, k_pr.dP, k_pr.p);
    mpz_powm(m_2, c, k_pr.dQ, k_pr.q);

    mpz_sub(h_1, m_1, m_2);
    mpz_mul(h_2, h_1, k_pr.qInv);
    mpz_powm_ui(h, h_2, 1, k_pr.p);

    mpz_mul(h_3, k_pr.q, h);
    mpz_add(m, m_2, h_3);
}
