/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#ifndef DATA_CONVERSION_PRIMATIVES_H
#define DATA_CONVERSION_PRIMATIVES_H

#include <gmp.h>

int I2OSP(unsigned int octet_str[], mpz_t i, unsigned long length);
int OS2IP(mpz_t i, unsigned int octet_str[], int length);

#endif
