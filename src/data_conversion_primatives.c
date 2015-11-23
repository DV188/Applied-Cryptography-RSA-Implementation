/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <string.h>

#include "data_conversion_primatives.h"

/*
 * This function converts a big integer into an octet string representation.
 * Parameters:
 *      octet_string - buffer to which the octet string will be assigned
 *      i - integer to be converted, big int
 *      length - length of the octet string
 * Returns:
 *      Returns an octet string via the octet_string parameter.
 */
int I2OSP(unsigned int octet_string[], mpz_t i, unsigned long length) {
    int index_c = 0;
    mpz_t len_test, tmp_byte;
    mpz_init(len_test);
    mpz_init(tmp_byte);

    mpz_ui_pow_ui(len_test, 256, length);
    if (mpz_cmp(i, len_test) >= 0)
        return(1);

    while (mpz_cmp_ui(i, 0) > 0) {
        mpz_mod_ui(tmp_byte, i, 256);
        octet_string[length - 1 - index_c] = mpz_get_ui(tmp_byte);
        mpz_fdiv_q_ui(i, i, 256);

        index_c++;
    }

    memset(octet_string, 0x00, length - index_c);

    return(0);
}

/*
 * This function converts an octet string into a big int representation.
 * Parameters:
 *      i - big integer to be returned
 *      octet_string - octet string to be converted into an integer
 *      length - length of the octet string
 * Returns:
 *      Returns a big int via the i parameter.
 */
int OS2IP(mpz_t i, unsigned int octet_string[], int length) {
    mpz_t tmp_shift, tmp_mul;
    mpz_init(tmp_shift);
    mpz_init(tmp_mul);

    for (int j = length - 1; j >= 0; j--) {
        mpz_ui_pow_ui(tmp_shift, 256, length - 1 - j);
        mpz_mul_ui(tmp_mul, tmp_shift, octet_string[j]);
        mpz_add(i, i, tmp_mul);
    }

    return 0;
}

/*
 * Prints and octet string, mostly for testing purposes.
 * Parameters:
 *      octet_string - octet string for which you would like printed
 *      octet_string_length - length of the octet string
 * Returns:
 *      Prints octet string without returning a value.
 */
void print_octet_string(unsigned int *octet_string, int octet_string_length) {
    for (int i = 0; i < octet_string_length; i++)
        printf("%d ", octet_string[i]);

    printf("\n");
}
