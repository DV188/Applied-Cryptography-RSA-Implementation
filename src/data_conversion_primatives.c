/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <string.h>

#include "data_conversion_primatives.h"

int I2OSP(unsigned int octet_str[], mpz_t i, unsigned long length) {
    int index_c = 0;
    mpz_t len_test, tmp_byte;
    mpz_init(len_test);
    mpz_init(tmp_byte);

    mpz_ui_pow_ui(len_test, 256, length);
    if (mpz_cmp(i, len_test) >= 0)
        return(1);

    while (mpz_cmp_ui(i, 0) > 0) {
        mpz_mod_ui(tmp_byte, i, 256);
        octet_str[length - 1 - index_c] = mpz_get_ui(tmp_byte);
        mpz_fdiv_q_ui(i, i, 256);

        index_c++;
    }

    memset(octet_str, 0x00, length - index_c);

    return(0);
}

int OS2IP(mpz_t i, unsigned int octet_str[], int length) {
    mpz_t tmp_shift, tmp_mul;
    mpz_init(tmp_shift);
    mpz_init(tmp_mul);

    for (int j = length - 1; j >= 0; j--) {
        mpz_ui_pow_ui(tmp_shift, 256, length - 1 - j);
        mpz_mul_ui(tmp_mul, tmp_shift, octet_str[j]);
        mpz_add(i, i, tmp_mul);
    }

    return 0;
}

