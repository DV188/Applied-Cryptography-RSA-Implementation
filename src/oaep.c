/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <string.h>
#include <gmp.h>

#include "oaep.h"
#include "RSA.h"
#include "data_conversion_primatives.h"

void RSAEP_OAEP_encrypt(
        unsigned int ciphertext_octet_string[],
        public_key k_pu,
        unsigned int message_octet_string[],
        int message_octet_string_length,
        unsigned int label_octet_string[],
        int label_octet_string_length) {

    int modulus_length = mpz_sizeinbase(k_pu.n, 10);
    int hash_length = 40; //For SHA-1 the length of the hash created is 40 characters long.

    mpz_t SHA_length_check;
    mpz_init_set_ui(SHA_length_check, 2305843009213693951); //2^61 - 1

    mpz_t m, c;
    mpz_init(m);
    mpz_init(c);

    //Length Checking
    if (mpz_cmp_ui(SHA_length_check, label_octet_string_length) < 0)
        printf("Label octet string is too long for SHA-1.\n");

    if (message_octet_string_length > modulus_length - 2*hash_length - 2) {
        printf("Message octet string is too long.\n");
        printf("%d > %d\n", message_octet_string_length, modulus_length - 2*hash_length - 2);
    }

    //EME-OAEP Encoding
    if (label_octet_string == NULL) {
        mpz_t empty_string;
        mpz_init(empty_string);

        I2OSP(label_octet_string, empty_string, 1);
    }

    //Generate Label Hash
    mpz_t label_hash;
    mpz_init(label_hash);
    SHA1(label_hash, label_octet_string);

    //Generate PS octet string
    mpz_t PS_value;
    mpz_init(PS_value);

    unsigned int PS_length = modulus_length - message_octet_string_length - 2*hash_length - 2;
    unsigned int PS_octet_string[PS_length];
    memset(PS_octet_string, 0, sizeof(PS_octet_string));

    I2OSP(PS_octet_string, PS_value, PS_length);

    //Concatenate Data Block
    //data_block = hash_length || PS || 0x01 || message_octet_string;

    //Mask Data Block
    //db_mask = MGF(random_seed_octet_string, modulus_length - hash_length - 1);
    //masked_db = XOR(data_block, db_mask);
    //seed_mask = MGF(masked_db, hash_length);
    //masked_seed = XOR(seed, seed_mask);

    //Encoded Message of Modulus Length Octets
    //m = OS2IP(0x00 || masked_seed || masked_db);

    //RSA Encryption
    OS2IP(m, message_octet_string, message_octet_string_length);

    RSAEP(c, m, k_pu);

    I2OSP(ciphertext_octet_string, c, mpz_sizeinbase(c, 10));
}

void SHA1(mpz_t label_hash, unsigned int octet_string[]) {
    mpz_init_set_str(label_hash, "1234567890123456789012345678901234567890", 10);
}