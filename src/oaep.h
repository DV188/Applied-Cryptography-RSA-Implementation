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

void RSAEP_OAEP_encrypt(
        unsigned int ciphertext_octet_string[],
        public_key k_pu,
        unsigned int message_octet_string[],
        int message_octet_string_length,
        unsigned int label_octet_string[],
        int label_octet_string_length);

void SHA1(mpz_t label_hash, unsigned int octet_string[]);

#endif
