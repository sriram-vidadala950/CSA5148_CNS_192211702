#include <stdio.h>

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    int x; // Declare loop variable outside the for loop
    for (x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

int main() {
    char ciphertext[100], plaintext[100];
    int a, b, a_inv, x, y;
    int i;
    
    // The most frequent letters in ciphertext are 'B' and 'U'
    // 'B' corresponds to 'E' and 'U' corresponds to 'T'
    int c1 = 1, p1 = 4; // B -> E
    int c2 = 20, p2 = 19; // U -> T

    // Solve the equations to find a and b
    // a * p1 + b = c1 (mod 26)
    // a * p2 + b = c2 (mod 26)
    x = (c1 - c2 + 26) % 26;
    y = (p1 - p2 + 26) % 26;
    
    // a = x * modInverse(y, 26) (mod 26)
    a = (x * modInverse(y, 26)) % 26;
    b = (c1 - a * p1 + 26 * 26) % 26;

    printf("The keys are: a = %d, b = %d\n", a, b);

    // Calculate modular inverse of a
    a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Multiplicative inverse for a = %d does not exist.\n", a);
        return 1;
    }

    // Input the ciphertext
    printf("Enter the ciphertext: ");
    scanf("%s", ciphertext);

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
    plaintext[i] = '\0'; // Null-terminate the plaintext

    // Output the decrypted text
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

