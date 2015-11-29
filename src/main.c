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

int main(int arc, char *argv[]) {
    char input_message [1000];
    char continue_response[3];
    char yes[] = "yes";

    mpz_t message; //Big int message to be encrypted.
    mpz_t ciphertext; //Big int ciphertext to be decrypted.
    mpz_t p; //First Prime.
    mpz_t q; //Sectond Prime.
    mpz_t e; //Public Exponent

    unsigned int message_length;

    int prime_size;
    int ciphertext_length;
    int correct_answer = 0;

    public_key k_pu; //Stuct representation of a public key.
    private_key k_pr; //Stuct representation of a private key using CRT.

    printf("----------------------------------------------------------------\n");
    printf("--------------  The RSA Public Key Cryptosystem   --------------\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("Please enter a interger value you would like to encrypt:\n");
    scanf("%s", input_message);
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("Please enter the size of primes you would like to generate.\n");
    printf("Values are typically 512 or 1024 for an RSA modulus of size 1024 or 2048:\n");
    scanf("%d", &prime_size);
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");

    mpz_init_set_str(message, input_message, 10); //Convert string to big int.
    message_length = mpz_sizeinbase(message, 10); //Get length of big int characters.

    //Create appropriate array length using the length of the message given.
    unsigned int octet_string[message_length];

    memset(octet_string, 0, sizeof(octet_string)); //Initialize array elements to 0.

    //Initialize big int variables;
    mpz_init(p);
    mpz_init(q);
    mpz_init(ciphertext);

    mpz_init_set_ui(e, 65537); //Setting public exponent according to pkcs#1 v2.1

    gmp_printf("For this demonstration, the public exponent e has been set to %Zd.\n", e);
    printf("Where ed = 1 mod lambda(n), pkcs#1 v2.1\n");
    printf("\n");
    printf("----------------------------------------------------------------\n");
    printf("\n");
    printf("Generating the public key for your message:\n");

    while (correct_answer == 0) {
        correct_answer = 1;

        k_pu = generate_public_key(p, q, e, prime_size); //Generates a public key using primes and public exponent.

        print_public_key(k_pu);
        printf("\n");

        printf("----------------------------------------------------------------\n");
        printf("\n");
        printf("Generating the private key for your message using large primes and the public exponent:\n");

        k_pr = generate_private_key(p, q, e); //Generates corresponding private key.

        print_private_key(k_pr);
        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("\n");

        printf("Converting your message into its octet string representation:\n");

        I2OSP(octet_string, message, message_length); //Converts message to octect_string.

        print_octet_string(octet_string, message_length);

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("\n");
        printf("Using this octet string, we will run RSA to encrypt the message.\n");

        OS2IP(message, octet_string, message_length); //Octet string to int to be used in RSA encrypt.

        int return_code = RSAEP(ciphertext, message, k_pu); //Runs RSA encypt.

        if (!return_code) {
            printf("The message representation is out of range. Would you like to retry? (yes, no)\n");
            scanf("%s", continue_response);
            printf("%s\n", continue_response);

            if (strcmp(continue_response, yes) == 0) {
                printf("here\n");
                correct_answer = 0;
            }
        }

        printf("The ciphertext produced is as follows:\n");
        gmp_printf("%Zd\n", ciphertext);

        ciphertext_length = mpz_sizeinbase(ciphertext, 10); //Saves the length of the ciphertext.
        unsigned int ciphertext_octet_string[ciphertext_length];
        memset(ciphertext_octet_string, 0, sizeof(ciphertext_octet_string));

        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("\n");
        printf("This ciphertext is again converted into an octet string to pad before being passed to the decrypter.\n");

        I2OSP(ciphertext_octet_string, ciphertext, ciphertext_length); //Ciphertext to octet string.

        OS2IP(ciphertext, ciphertext_octet_string, ciphertext_length); //Convert back to int for RSADP.

        return_code = RSADP(message, ciphertext, k_pr); //Runs RSA decrypt.

        if (!return_code) {
            printf("The ciphertext representation is out of range. Would you like to retry? (yes, no)\n");
            scanf("%s", continue_response);
            printf("%s\n", continue_response);

            if (strcmp(continue_response, yes) == 0) {
                printf("here\n");
                correct_answer = 0;
            }
        }


        printf("\n");
        printf("----------------------------------------------------------------\n");
        printf("\n");
        printf("Finally, the cipher text is decrypted to give the following results:\n");
        gmp_printf("%Zd\n", message);
    }
}
