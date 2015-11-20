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
    mpz_init_set_str(i, "505653012503429218243943633705672380046318162980074400525290686010978535210508251025371556786334751948415457926276892598751961027794016968235973613925881804782472056690499897096340749266251887257171654630228493856549694979043602485084236106517977998198816346622004351187096835097200490691844506811161067102443", 10);

    unsigned int length = mpz_sizeinbase(i, 10);
    unsigned int octet_string[length];
    memset(octet_string, 0, sizeof(octet_string));

    I2OSP(octet_string, i, length);

    int prime_size = 513;
    mpz_t p, q, e;
    public_key k_pu;

    mpz_init(p);
    mpz_init(q);

    mpz_init_set_ui(e, 65537);

    k_pu = generate_public_key(p, q, e, prime_size);

    RSAEP_OAEP_encrypt(k_pu, octet_string, octet_string);
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
