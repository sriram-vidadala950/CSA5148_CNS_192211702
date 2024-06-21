#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main() {
    char plaintext[256];
    char key[27];
    char ciphertext[256];
    int i;
    // Example key: mapping the alphabet to a different set of letters
    // Ensure the key is a permutation of the alphabet and contains 26 unique characters
    strcpy(key, "QWERTYUIOPLKJHGFDSAZXCVBNM");
    // Input plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the trailing newline character
    // Encrypt the plaintext
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            int index = tolower(plaintext[i]) - 'a';
            ciphertext[i] = isupper(plaintext[i]) ? toupper(key[index]) : key[index];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

