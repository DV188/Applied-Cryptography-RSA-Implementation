/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#ifndef OAEP_H
#define OAEP_H

#include <gmp.h>
#include "key_generation.h" 

unsigned int RSAEP_OAEP_encrypt(
        public_key k_pu,
        unsigned int *message_octet_string,
        unsigned int *label_octet_string);

#endif
