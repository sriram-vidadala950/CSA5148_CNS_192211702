#include <stdio.h>
#include <string.h>

// Function to perform modulo 26 operation
int mod26(int x) {
    return (x % 26 + 26) % 26;
}

// Function to multiply 2x2 matrix with 2x1 vector and take modulo 26
void matrixMultiply(int key[2][2], int vector[2], int result[2]) {
    result[0] = mod26(key[0][0] * vector[0] + key[0][1] * vector[1]);
    result[1] = mod26(key[1][0] * vector[0] + key[1][1] * vector[1]);
}

// Function to convert character to integer
int charToInt(char c) {
    return c - 'a';
}

// Function to convert integer to character
char intToChar(int n) {
    return n + 'a';
}

int main() {
    char plaintext[] = "meetmeattheusualplaceattenratherthaneightoclock";
    int key[2][2] = {{9, 4}, {5, 7}};
    int inverseKey[2][2] = {{21, 14}, {11, 1}};
    int length = strlen(plaintext);
    int i; // Declare i here for compatibility with older C standards

    // Ensure the plaintext length is even by padding with 'x' if necessary
    if (length % 2 != 0) {
        plaintext[length] = 'x';
        plaintext[length + 1] = '\0';
        length++;
    }

    printf("Original Plaintext: %s\n", plaintext);

    // Encrypt the plaintext
    char ciphertext[length + 1];
    ciphertext[length] = '\0';

    // Encrypting process
    for (i = 0; i < length; i += 2) {
        int vector[2] = {charToInt(plaintext[i]), charToInt(plaintext[i + 1])};
        int result[2];
        matrixMultiply(key, vector, result);
        ciphertext[i] = intToChar(result[0]);
        ciphertext[i + 1] = intToChar(result[1]);
    }

    printf("Encrypted Ciphertext: %s\n", ciphertext);

    // Decrypt the ciphertext
    char decryptedText[length + 1];
    decryptedText[length] = '\0';

    // Decrypting process
    for (i = 0; i < length; i += 2) {
        int vector[2] = {charToInt(ciphertext[i]), charToInt(ciphertext[i + 1])};
        int result[2];
        matrixMultiply(inverseKey, vector, result);
        decryptedText[i] = intToChar(result[0]);
        decryptedText[i + 1] = intToChar(result[1]);
    }

    printf("Decrypted Plaintext: %s\n", decryptedText);

    return 0;
}

