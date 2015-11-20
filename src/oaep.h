/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#ifndef OAEP_H
#define OAEP_H

#include "key_generation.h" 

void RSAES_OAEP_encrypt(
        unsigned int ciphertext_octet_string[],
        public_key k_pu,
        unsigned int message_octet_string[],
        int message_octet_string_length,
        unsigned int label_octet_string[],
        int label_octet_string_length);

void RSAES_OAEP_decrypt(
        mpz_t message,
        private_key k_pr,
        unsigned int ciphertext_octet_string[],
        int ciphertext_octet_string_length,
        unsigned int label_octet_string[],
        int label_octet_string_length);

void SHA1(mpz_t label_hash, unsigned int octet_string[]);

#endif
