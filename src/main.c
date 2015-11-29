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
#include "RSA.h" 
#include "data_conversion_primatives.h" 

// int main(int arc, char *argv[]) {
//     char input_message [1000];
// 
//     mpz_t message; //Big int message to be encrypted.
//     mpz_t p; //First Prime.
//     mpz_t q; //Sectond Prime.
//     mpz_t e; //Public Exponent
// 
//     unsigned int message_length;
// 
//     int prime_size;
// 
//     public_key k_pu; //Stuct representation of a public key.
//     private_key k_pr; //Stuct representation of a private key using CRT.
// 
//     printf("----------------------------------------------------------------\n");
//     printf("--------------  The RSA Public Key Cryptosystem   --------------\n");
//     printf("----------------------------------------------------------------\n");
//     printf("\n");
//     printf("Please enter a interger value you would like to encrypt:\n");
//     scanf("%s", input_message);
//     printf("\n");
//     printf("Please enter the size of primes you would like to generate.\n");
//     printf("Values are typically 512 or 1024 for an RSA modulus of size 1024 or 2048:\n");
//     scanf("%d", &prime_size);
//     printf("\n");
// 
//     mpz_init_set_str(message, input_message, 10); //Convert string to big int.
//     message_length = mpz_sizeinbase(message, 10); //Get length of big int characters.
// 
//     //Create appropriate array length using the length of the message given.
//     unsigned int octet_string[message_length];
//     unsigned int ciphertext_octet_string[message_length];
// 
//     //Initialize array elements to 0.
//     memset(octet_string, 0, sizeof(octet_string));
//     memset(ciphertext_octet_string, 0, sizeof(ciphertext_octet_string));
// 
//     //Initialize big int variables;
//     mpz_init(p);
//     mpz_init(q);
// 
//     mpz_init_set_ui(e, 65537); //Setting public exponent according to pkcs#1 v2.1
// 
//     gmp_printf("For this demonstration, the public exponent e has been set to %Zd.\n", e);
//     printf("Where ed = 1 mod lambda(n), pkcs#1 v2.1\n");
//     printf("\n");
//     printf("Generating the public key for your message:\n");
// 
//     k_pu = generate_public_key(p, q, e, prime_size); //Generates a public key using primes and public exponent.
// 
//     print_public_key(k_pu);
//     printf("\n");
// 
//     printf("Generating the private key for your message using large primes and the public exponent:\n");
// 
//     k_pr = generate_private_key(p, q, e); //Generates corresponding private key.
// 
//     print_private_key(k_pr);
//     printf("\n");
// 
//     printf("Converting your message into its octet string representation:\n");
// 
//     I2OSP(octet_string, message, message_length); //Converts message to octect_string.
// 
//     print_octet_string(octet_string, message_length);
//     printf("\n");
//     printf("Using this octet string, we will run RSA using OAEP to encrypt the message.\n");
//     printf("The ciphertext is output as another octet string:\n");
// 
//     RSAES_OAEP_encrypt(ciphertext_octet_string, k_pu, octet_string, message_length, octet_string, message_length); //Runs RSA encrypting algorithm using octet strings, returns ciphertext octet string.
// 
//     print_octet_string(ciphertext_octet_string, message_length);
//     printf("\n");
// 
//     // RSAES_OAEP_decrypt(m, k_pr, ciphertext_octet_string, mpz_sizeinbase(k_pu.n, 10), octet_string, length);
// }

int main(int arc, char *argv[]) {
    mpz_t message, message_2, message_3, ciphertext, ciphertext_2;
    mpz_t p, q, e;
    mpz_init(p);
    mpz_init(q);
    mpz_init(message);
    mpz_init(message_2);
    mpz_init(message_3);
    mpz_init(ciphertext);
    mpz_init(ciphertext_2);

    int prime_size = 512;

    public_key k_pu;
    private_key k_pr;

    mpz_init_set_str(message, "188", 10);

    int message_length = mpz_sizeinbase(message, 10);
    unsigned int message_octet_string[message_length];

    memset(message_octet_string, 0, sizeof(message_octet_string));

    I2OSP(message_octet_string, message, message_length);

    print_octet_string(message_octet_string, message_length);

    OS2IP(message_2, message_octet_string, message_length);

    gmp_printf("%Zd\n", message_2);

    mpz_init_set_ui(e, 65537); //Setting public exponent according to pkcs#1 v2.1
    k_pu = generate_public_key(p, q, e, prime_size);
    k_pr = generate_private_key(p, q, e);

    RSAEP(ciphertext, message_2, k_pu);

    gmp_printf("%Zd\n", ciphertext);

    int ciphertext_length = mpz_sizeinbase(ciphertext, 10);
    unsigned int ciphertext_octet_string[ciphertext_length];
    memset(ciphertext_octet_string, 0, sizeof(ciphertext_octet_string));

    I2OSP(ciphertext_octet_string, ciphertext, ciphertext_length);

    print_octet_string(ciphertext_octet_string, ciphertext_length);

    OS2IP(ciphertext_2, ciphertext_octet_string, ciphertext_length);

    RSADP(message_3, ciphertext_2, k_pr);

    gmp_printf("%Zd\n", message_3);
}
