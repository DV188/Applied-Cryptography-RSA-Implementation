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
#include "key_generation.h" 

void RSAEP(mpz_t c, const mpz_t m, const public_key k_pu);
void RSADP_texbook(mpz_t m, const mpz_t c, const private_key_textbook k_pr);
void RSADP(mpz_t m, const mpz_t c, const private_key k_pr);

#endif
