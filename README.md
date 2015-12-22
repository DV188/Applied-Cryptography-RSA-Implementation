Applied-Cryptography-RSA-Implementation
=======================================

Introduction
------------

RSA is a popular public key cryptosystem.  It uses three functions, key generation, encryption, and decryption, in conjunction with a public key and a private key to share a given message.  RSA is one of the most widely used cryptosystems in the world and one of the best known.  It can be used for both encryption/decryption or signature and verification.  The system is built upon the difficulty of factoring large numbers with some similarities to the Diffie-Hellman cryptosystem.  For this project, RSA will be implemented using OAEP padding and Chinese Remainder Theorem for decryption.  RSA variants will then be compared to the standard.

Compilation Instructions
------------------------

Included with this project is a Makefile for compiling and linking the code.  I used the GNU MP (gmp.h) library to handle big numbers.  I had some trouble linking the library to my project however in the Makefile I have included compiler flags for the path of the gmp library located in /gmplib.

For compilation using GCC:
- $ make

To run:
- $ ./RSA

Notes
-----

In my project I used the Rabin-Miller test for creating my primes.  The function I used creates prime of a specific size in binary.  The Rabin-Miller primatlity test has an increasing probability to fail given larger sizes of prime numbers to be generated.  If these bugs occur I do let the program complete its process as an educational tool for seeing how the result will be skewed as opposed to killing the program.

I was unable to get my SHA1 hash to work properly and could not fully implement OAEP padding.  I did my best to include the steps involved with OAEP and document the process but I have ran out of time to implement a perfect solution.  Please refer to Documentation/RSA-OAEP\ Explained.pdf for a write up of how RSA-OAEP is to function.

There is also a OpenSSL directory included with my project.  I wrote a bash script that utilizes OpenSSL to create real RSA keys and do real encryption.  If OpenSSL is installed the script should work, sh RSA.sh to run.

Please find example runs of all the code in the /Documentation folder included, RSA\ Example.txt and RSA\ Script\ Example.txt.
