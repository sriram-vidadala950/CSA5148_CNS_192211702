#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Function to find the multiplicative inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    int x;
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
int main() {
    int a, b;
    char plaintext[100], ciphertext[100];
    int a_inv;
    int i;  // Declare loop variable here
    // Input values for a and b
    printf("Enter the value of a (should be coprime with 26): ");
    scanf("%d", &a);
    printf("Enter the value of b: ");
    scanf("%d", &b);
    // Calculate the multiplicative inverse of a modulo 26
    a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Multiplicative inverse for a = %d does not exist.\n", a);
        return 1;
    }
    // Input the plaintext
    printf("Enter the plaintext: ");
    scanf("%s", plaintext);

    // Encrypt the plaintext
    for (i = 0; plaintext[i] != '\0'; i++) {
        char p = plaintext[i];
        if (p >= 'a' && p <= 'z') {
            p = p - 'a'; // Convert to 0-25 range
            ciphertext[i] = (char) (((a * p + b) % 26) + 'a');
        } else if (p >= 'A' && p <= 'Z') {
            p = p - 'A'; // Convert to 0-25 range
            ciphertext[i] = (char) (((a * p + b) % 26) + 'A');
        } else {
            ciphertext[i] = p; // Non-alphabetic characters are not encrypted
        }
    }
    ciphertext[strlen(plaintext)] = '\0'; // Null-terminate the ciphertext
    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    // Decrypt the ciphertext
    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (c >= 'a' && c <= 'z') {
            c = c - 'a'; // Convert to 0-25 range
            plaintext[i] = (char) (((a_inv * (c - b + 26)) % 26) + 'a');
        } else if (c >= 'A' && c <= 'Z') {
            c = c - 'A'; // Convert to 0-25 range
            plaintext[i] = (char) (((a_inv * (c - b + 26)) % 26) + 'A');
        } else {
            plaintext[i] = c; // Non-alphabetic characters are not decrypted
        }
    }
    plaintext[strlen(ciphertext)] = '\0'; // Null-terminate the decrypted plaintext
    // Output the decrypted text
    printf("Decrypted text: %s\n", plaintext);
    return 0;
}

