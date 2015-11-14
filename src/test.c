/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <gmp.h>

#include "RSA.h" 
#include "key_generation.h" 
#include "test.h" 

void test_RSA_textbook(void) {
    int prime_size = 513;
    mpz_t p, q, e, m, c;
    public_key k_pu;
    // private_key k_pr;
    private_key_textbook k_pr;

    mpz_init(p);
    mpz_init(q);
    mpz_init(c);
    mpz_init_set_str(m, "427680787658796414495478412765818481773700031964971550032485995462094541318172071699678633526190831000613031464300541848882252073989630802044992230370499993349891121354055409063481101792420859297579606741599372692821291104228771117776673746157967849667351681259816188574800065511460953723930836865732656293632", 10);

    mpz_init_set_ui(e, 65537);

    k_pu = generate_public_key(p, q, e, prime_size);
    // k_pr = generate_private_key(p, q, e);
    k_pr = generate_private_key_textbook(p, q, e);

    // print_public_key(k_pu);
    // print_private_key_textbook(k_pr);

    printf("Message size: %zu\n", mpz_sizeinbase(m, 2));
    printf("Prime Size: %zu\n", mpz_sizeinbase(p, 2));

    gmp_printf("\n%Zd\n", m);

    RSAEP(c, m, k_pu);
    gmp_printf("\n%Zd\n", c);

    RSADP_texbook(m, c, k_pr);
    gmp_printf("\n%Zd\n", m);
}
