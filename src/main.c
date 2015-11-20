/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <string.h>

#include "oaep.h" 
#include "data_conversion_primatives.h" 

int main(int arc, char *argv[]) {
    mpz_t i;
    mpz_init_set_str(i, "505653012503429218243943633705672380046318162980074400", 10);

    unsigned int length = mpz_sizeinbase(i, 10);
    unsigned int octet_string[length];
    unsigned int ciphertext_octet_string[1000];
    unsigned int message_octet_string[length];

    memset(octet_string, 0, sizeof(octet_string));
    memset(ciphertext_octet_string, 0, sizeof(ciphertext_octet_string));
    memset(message_octet_string, 0, sizeof(message_octet_string));

    I2OSP(octet_string, i, length);

    int prime_size = 512;
    mpz_t p, q, e, m;
    public_key k_pu;
    private_key k_pr;

    mpz_init(p);
    mpz_init(q);
    mpz_init(m);

    mpz_init_set_ui(e, 65537);

    k_pu = generate_public_key(p, q, e, prime_size);
    k_pr = generate_private_key(p, q, e);

    RSAES_OAEP_encrypt(ciphertext_octet_string, k_pu, octet_string, length, octet_string, length);
    RSAES_OAEP_decrypt(message_octet_string, k_pr, ciphertext_octet_string, mpz_sizeinbase(k_pu.n, 10), octet_string, 310);
}

// int main(int arc, char *argv[]) {
//     int prime_size = 513;
//     mpz_t p, q, e, m, c;
//     public_key k_pu;
//     private_key k_pr;
// 
//     mpz_init(p);
//     mpz_init(q);
//     mpz_init(c);
//     mpz_init_set_str(m, "427680787658796414495478412765818481773700031964971550032485995462094541318172071699678633526190831000613031464300541848882252073989630802044992230370499993349891121354055409063481101792420859297579606741599372692821291104228771117776673746157967849667351681259816188574800065511460953723930836865732656293632", 10);
// 
//     mpz_init_set_ui(e, 65537);
// 
//     k_pu = generate_public_key(p, q, e, prime_size);
//     k_pr = generate_private_key(p, q, e);
// 
//     printf("Message size: %zu\n", mpz_sizeinbase(m, 2));
//     printf("Prime Size: %zu\n", mpz_sizeinbase(p, 2));
// 
//     gmp_printf("\n%Zd\n", m);
// 
//     RSAEP(c, m, k_pu);
//     gmp_printf("\n%Zd\n", c);
// 
//     RSADP(m, c, k_pr);
//     gmp_printf("\n%Zd\n", m);
// 
//     return 0;
// }
