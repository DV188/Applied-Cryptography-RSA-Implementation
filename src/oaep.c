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

/* Encrypts a message using oaep padding combined with RSA encrypt.
 * Parameters:
 *      ciphertext_octet_string - buffer where the ciphertext will be stored in the form of a string octet
 *      k_pu - RSA public key
 *      message_octet_string - message that has been converted to its octet string representation
 *      message_octet_string_length - length of the message octet string
 *      label_octet_string - optional label whose association with the message is to be verified, octet string
 *      label_octet_string_length - length of label octet string
 * Returns:
 *      Data is written to the ciphertext_octet_string in the form of an octet string.
 */
void RSAES_OAEP_encrypt(
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

/* Decrypts a ciphertext that uses oaep padding and RSA decrypt.
 * Parameters:
 *      message - buffer for the big int representation of the message
 *      k_pr - RSA private key using CRT
 *      ciphertext_octet_string - ciphertext to decrypt in the form of an octet string
 *      ciphertext_octet_string_length - length of the ciphertext octet string
 *      label_octet_string - optional label whose association with the message is to be verified, octet string
 *      label_octet_string_length - length of label octet string
 * Returns:
 *      Data is written to the message variable in the form of a big int.
 */
void RSAES_OAEP_decrypt(
        mpz_t message,
        private_key k_pr,
        unsigned int ciphertext_octet_string[],
        int ciphertext_octet_string_length,
        unsigned int label_octet_string[],
        int label_octet_string_length) {

    mpz_t n, c;
    mpz_init(n);
    mpz_init(c);

    mpz_mul(n, k_pr.p, k_pr.q);

    int modulus_length = mpz_sizeinbase(n, 10);
    int hash_length = 40; //For SHA-1 the length of the hash created is 40 characters long.

    mpz_t SHA_length_check;
    mpz_init_set_ui(SHA_length_check, 2305843009213693951); //2^61 - 1

    //Length Checking
    if (mpz_cmp_ui(SHA_length_check, label_octet_string_length) < 0)
        printf("Label octet string is too long for SHA-1.\n");

    if (ciphertext_octet_string_length != modulus_length)
        printf("Decryption message octet string is too long.\n");

    if (modulus_length < 2*hash_length + 2)
        printf("Decryption error\n");

    //RSA Decryption
    OS2IP(c, ciphertext_octet_string, ciphertext_octet_string_length);

    RSADP(message, c, k_pr);

    //EM = I2OSP(m, modulus_length);

    //EME-OAEP Decoding

    if (label_octet_string == NULL) {
        mpz_t empty_string;
        mpz_init(empty_string);

        I2OSP(label_octet_string, empty_string, 1);
    }

    //Generate Label Hash
    mpz_t label_hash;
    mpz_init(label_hash);
    SHA1(label_hash, label_octet_string);

    //Separate encoded message EM
    //EM = Y || masked_seed || masked_db;

    //seed_mask = MGF(masked_db, hash_length);
    //seed = XOR(masked_seed, db_mask);

    //Separate Data Block
    //DB = hash_length || PS || 0x01 || M;
    //return(M);
}

void SHA1(mpz_t label_hash, unsigned int octet_string[]) {
    mpz_init_set_str(label_hash, "1234567890123456789012345678901234567890", 10);
}
