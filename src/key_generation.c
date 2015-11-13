/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <time.h>

#include "key_generation.h"
#include "miller-rabin.h"

//Functions

/*
 * Creates a public key used for asymmetric cryptography.
 * Parameters:
 *      n - mpz_t value representing n, the RSA modulus
 *      e - mpz_t value resprsenting e, the RSA private exponent
 * Returns:
 *      k_pu - struct representation of the RSA public key
 */
public_key set_public_key(const mpz_t n, const mpz_t e) {
    public_key k_pu;

    //Initialize values of the public key to 0.
    mpz_init(k_pu.n);
    mpz_init(k_pu.e);

    //Assign mpz_t to key.
    mpz_set(k_pu.n, n);
    mpz_set(k_pu.e, e);

    return(k_pu);
}

/*
 * Creates a private key used for asymmetric cryptography.
 * Parameters:
 *      n - modulous of the  RSA private key
 *      d - private exponent of the  RSA private key
 * Returns:
 *      k_pr - struct representation of the RSA private key
 */
private_key_textbook set_private_key_texbook(const mpz_t n, const mpz_t d) {
    private_key_textbook k_pr;

    //Initialize values of the private key to 0.
    mpz_init(k_pr.n);
    mpz_init(k_pr.d);

    //Assign mpz_t to key.
    mpz_set(k_pr.n, n);
    mpz_set(k_pr.d, d);

    return(k_pr);
}

/*
 * Creates a private key used for asymmetric cryptography.
 * Parameters:
 *      p - first factor of the RSA private key
 *      q - second factor of the RSA private key
 *      dP - first factor CRT exponent of the RSA private key
 *      dQ - second factor CRT exponent of the RSA private key
 *      qInv - CRT coefficient of the RSA private key
 * Returns:
 *      k_pr - struct representation of the RSA private key using CRT
 */
private_key set_private_key(const mpz_t p, const mpz_t q, const mpz_t dP, const mpz_t dQ, const mpz_t qInv) {
    private_key k_pr;

    //Initialize values of the private key to 0.
    mpz_init(k_pr.p);
    mpz_init(k_pr.q);
    mpz_init(k_pr.dP);
    mpz_init(k_pr.dQ);
    mpz_init(k_pr.qInv);

    //Assign mpz_t to key.
    mpz_set(k_pr.p, p);
    mpz_set(k_pr.q, q);
    mpz_set(k_pr.dP, dP);
    mpz_set(k_pr.dQ, dQ);
    mpz_set(k_pr.qInv, qInv);

    return(k_pr);
}

/*
 * Prints the public key to std out.
 * Parameters:
 *      k_pu - struct public_key representing the public key
 */
void print_public_key(public_key k_pu) {
    gmp_printf("Public Key:\n(%Zd,\n %Zd)\n", k_pu.n, k_pu.e);
}

/*
 * Prints the private key to std out.
 * Parameters:
 *      k_pr - struct private_key representing the private key.
 */
void print_private_key(private_key k_pr) {
    gmp_printf("Private Key:\n(%Zd,\n %Zd,\n %Zd,\n %Zd,\n %Zd)\n", k_pr.p, k_pr.q, k_pr.dP, k_pr.dQ, k_pr.qInv);
}

/*
 * Prints the textbook private key to std out.
 * Parameters:
 *      k_pr - struct private_key representing the private key texbook.
 */
void print_private_key_textbook(private_key_textbook k_pr) {
    gmp_printf("Private Key:\n(%Zd,\n %Zd)\n", k_pr.n, k_pr.d);
}

/*
 * Generates a public key for key generation in RSA.
 * Parameters:
 *      p - initialized mpz_t value where prime p will be stored
 *      q - initialized mpz_t value where prime q will be stored
 *      e - initialized and set mpz_t value for public exponent e
 *      prime_size - size of the primes to be generated, usually 512 - 1024 bits
 * Returns:
 *      k_pu - public key for RSA
 */
public_key generate_public_key(mpz_t p, mpz_t q, const mpz_t e, int prime_size) {
    int return_code = 1;
    mpz_t n;
    public_key k_pu;

    generate_prime(p, prime_size);
    generate_prime(q, prime_size);

    while (mpz_cmp(p, q) == 0)
        generate_prime(q, prime_size);

    return_code = validate_e(e, p, q, prime_size);
    if (!return_code)
        printf("The public key exponent 'e' could not be validated.\n");

    mpz_init(n);
    mpz_mul(n, p, q);

    k_pu = set_public_key(n, e);

    return(k_pu);
}

/*
 * Generates a private key for key generation in RSA.
 * Parameters:
 *      p - initialized mpz_t value prime p
 *      q - initialized mpz_t value prime q
 *      e - initialized mpz_t value exponent e
 * Returns:
 *      k_pr - private key for textbook RSA
 */
private_key_textbook generate_private_key_textbook(const mpz_t p, const mpz_t q, const mpz_t e) {
    mpz_t n, d, p_minus_1, q_minus_1, phi_n;
    int return_code = 1;
    private_key_textbook k_pr;

    mpz_init(n);
    mpz_init(d);
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    mpz_init(phi_n);

    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);

    mpz_mul(phi_n, p_minus_1, q_minus_1);

    mpz_mul(n, p, q);

    return_code = mpz_invert(d, e, phi_n);

    if (return_code == 0)
        printf("Error inversing 'd'.\n");

    k_pr = set_private_key_texbook(n, d);

    return(k_pr);
}

/*
 * Generates a private key for key generation in RSA.
 * Parameters:
 *      p - initialized mpz_t value prime p
 *      q - initialized mpz_t value prime q
 *      e - initialized mpz_t value exponent e
 * Returns:
 *      k_pr - private key for RSA
 */
private_key generate_private_key(const mpz_t p, const mpz_t q, const mpz_t e) {
    mpz_t dP, dQ, qInv, p_minus_1, q_minus_1;
    int return_code = 1;
    private_key k_pr;

    mpz_init(dP);
    mpz_init(dQ);
    mpz_init(qInv);
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);

    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);

    return_code = mpz_invert(dP, e, p_minus_1);
    if (!return_code)
        printf("Error inversing 'dP'.\n");

    return_code = mpz_invert(dQ, e, q_minus_1);
    if (!return_code)
        printf("Error inversing 'dQ'.\n");

    return_code = mpz_invert(qInv, q, p);
    if (!return_code)
        printf("Error inversing 'qInv'.\n");

    k_pr = set_private_key(p, q, dP, dQ, qInv);

    return(k_pr);
}

/*
 * Creates a prime number using the Miller-Rabin primality test.
 * Parameters:
 *      p - empty value for p, generate_prime saves its value to this variable
 *          p represents a large prime number to be used with RSA's n = pq
 *      prime_size - size of prime in bits, 512 is typical for an RSA modulus of 1024 bits
 * Returns:
 *      p - the input parameter p is also where this function stores the value returned
 */
void generate_prime(mpz_t p, int prime_size) {
    mpz_t max, two;

    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui (rand_state, time(NULL));

    mpz_init(max);
    mpz_init_set_ui(two, 2);
    mpz_mul_2exp(max, two, prime_size + 1);
    mpz_init(p);

    do {
        mpz_urandomm(p, rand_state, max);
        if (mpz_even_p(p)) continue;
        if (mpz_fdiv_ui(p, 3) == 0) continue;
        if (mpz_fdiv_ui(p, 5) == 0) continue;
        if (mpz_fdiv_ui(p, 7) == 0) continue;
    } while (miller_rabin(p, rand_state) == COMPOSITE);
}

/*
 * Validation of e must be performed to make sure our primes have been created correctly.
 * Parameters:
 *      p - prime number generated randomly
 *      q - prime number generated randomly
 *      prime_size - size of the prime in bits, must be the same as p and q
 * Returns:
 *      Returns 1 if function completes.
 *      If p and q do not properly validate, p and q will be changed.
 */
int validate_e(const mpz_t e, mpz_t p, mpz_t q, int prime_size) {
    mpz_t gcd;
    mpz_t lcm;

    mpz_init(gcd);
    mpz_init(lcm);

    mpz_lcm(lcm, p, q);
    mpz_gcd(gcd, e, lcm);

    while (mpz_get_ui(gcd) != 1) {
        generate_prime(p, prime_size);
        generate_prime(q, prime_size);

        while (mpz_cmp(p, q) == 0)
            generate_prime(q, prime_size);

        mpz_lcm(lcm, p - 1, q - 1);
        mpz_gcd(gcd, e, lcm);

        printf("Generating new primes.\n");
    }

    return(1);
}
