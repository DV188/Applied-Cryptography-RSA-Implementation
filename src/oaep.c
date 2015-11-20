/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include "oaep.h"
#include "data_conversion_primatives.h"

unsigned int RSAEP_OAEP_encrypt(
        public_key k_pu,
        unsigned int *message_octet_string,
        unsigned int *label_octet_string) {

    print_public_key(k_pu);
    print_octet_string(message_octet_string, 309);
    print_octet_string(label_octet_string, 309);

    return(0);
}
