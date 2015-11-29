#Danen Van De Ven
#100820351

#COMP 4109 - Final Project Code Implementation
#December 2015

#!/bin/bash

echo "What size modulus would you like?"
read modulus

echo "What file would you like the private and public keys to be written to?"
read keyfile

echo "----------------------------------------------------------------------------------------------------"

openssl genrsa -out $keyfile.pem $modulus #Generate public and private keys with modulus size specified, saves to $keyfile.pem.

echo ""

openssl rsa -in $keyfile.pem -out public.pem -outform PEM -pubout #Separates the public key so it is available to share.

echo "----------------------------------------------------------------------------------------------------"

echo "Files for your public/private key and just the public key have been created in this directory."

echo ""

ls -l #List files in directory.

echo "----------------------------------------------------------------------------------------------------"

echo "Please input the message you would like encrypted:"
read message

echo $message > message.txt

echo ""

echo "Your message has been written to message.txt."

echo ""

ls -l #list file in directory.

echo "----------------------------------------------------------------------------------------------------"

echo "We can now encrypt your message found in message.txt:"

openssl rsautl -encrypt -inkey public.pem -pubin -in message.txt -out ciphertext.ssl #Writes message.txt to ciphertext.ssl using RSA encryption.

echo "The encrypted message is stored in ciphertext.ssl."

echo ""

ls -l #list file in directory.

echo "----------------------------------------------------------------------------------------------------"

echo "Finally, the message can now be decrypted using the private key stored in the file specified earlier:"

openssl rsautl -decrypt -inkey $keyfile.pem -in ciphertext.ssl -out decrypted.txt

echo ""

ls -l

echo ""

echo "Your message:"

cat decrypted.txt;

echo "----------------------------------------------------------------------------------------------------"
