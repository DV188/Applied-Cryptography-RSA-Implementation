/*
 * Danen Van De Ven
 * 100820351
 *
 * COMP 4109 - Final Project
 * December 2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "RSA.h" 
#include "miller-rabin.h" 

//Main

int main(int arc, char *argv[]) {
    int prime_size = 512;
    mpz_t p, q, e, m, c;
    public_key k_pu;
    private_key k_pr;

    mpz_init(p);
    mpz_init(q);
    mpz_init(c);
    mpz_init_set_str(m, "4276807876587964144954784127658184817737000319649715500324859954620945413181720716996786335261908310006130314643005418488822520739896308020449922303", 10);

    mpz_init_set_ui(e, 65537);

    k_pu = generate_public_key(p, q, e, 512);
    k_pr = generate_private_key(p, q, e);

    print_public_key(k_pu);
    print_private_key(k_pr);

    gmp_printf("\n%Zd\n", m);

    RSAEP(c, m, k_pu);
    gmp_printf("\n%Zd\n", c);

    RSADP(m, c, k_pr);
    gmp_printf("\n%Zd\n", m);

    return 0;
}

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

/*
 * Computes the multiplicative inverse of a private key.
 * Parameters:
 *      result - where the result is stored
 *      exponent - public key exponent
 *      prime - the value of a prime, usually - 1
 * Returns:
 *      Returns 0 if functions cannot be inverted.
 */
int multiplicative_inverse(mpz_t result, const mpz_t exponent, const mpz_t prime) {
    return(mpz_invert(result, exponent, prime));
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

    return_code = multiplicative_inverse(dP, e, p_minus_1);
    if (!return_code)
        printf("Error inversing 'dP'.\n");

    return_code = multiplicative_inverse(dQ, e, q_minus_1);
    if (!return_code)
        printf("Error inversing 'dQ'.\n");

    return_code = multiplicative_inverse(qInv, q, p);
    if (!return_code)
        printf("Error inversing 'qInv'.\n");

    k_pr = set_private_key(p, q, dP, dQ, qInv);

    return(k_pr);
}

void RSAEP(mpz_t c,  const mpz_t m, const public_key k_pu) {
    if (mpz_cmp(m, k_pu.n) > 0)
        printf("Message representative out of range.\n");

    mpz_powm(c, m, k_pu.e, k_pu.n);
}

void RSADP(mpz_t m, const mpz_t c, const private_key k_pr) {
    mpz_t n, m_1, m_2, h, h_1, h_2, h_3;
    mpz_init(n);
    mpz_init(m_1);
    mpz_init(m_2);
    mpz_init(h);
    mpz_init(h_1);
    mpz_init(h_2);
    mpz_init(h_3);

    mpz_mul(n, k_pr.q, k_pr.p);

    if (mpz_cmp(c, n) > 0)
        printf("Ciphertext representative out of range.\n");

    
    mpz_powm(m_1, c, k_pr.dP, k_pr.p);
    mpz_powm(m_2, c, k_pr.dQ, k_pr.q);

    mpz_sub(h_1, m_1, m_2);
    mpz_powm_ui(h_2, k_pr.qInv, 1, k_pr.p);
    mpz_mul(h, h_1, h_2);

    mpz_mul(h_3, k_pr.q, h);
    mpz_add(m, m_2, h_3);
}
