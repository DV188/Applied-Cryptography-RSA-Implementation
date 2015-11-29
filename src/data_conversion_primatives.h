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

int I2OSP(unsigned int octet_string[], mpz_t i, unsigned long length);
int OS2IP(mpz_t i, unsigned int octet_string[], int length);

void print_octet_string(unsigned int *octet_string, int octet_string_length);

#endif
