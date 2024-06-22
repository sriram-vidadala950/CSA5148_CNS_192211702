#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int main() {
    char keyword[] = "CIPHER";
    char plaintext[1000];
    char ciphertext[1000];
    char keyAlphabet[ALPHABET_SIZE];
    int i, j, k;
    
    // Convert keyword to uppercase and remove duplicates
    int keywordLen = strlen(keyword);
    for (i = 0; i < keywordLen; i++) {
        keyword[i] = toupper(keyword[i]);
    }
    
    // Initialize keyAlphabet with the keyword letters
    k = 0;
    for (i = 0; i < keywordLen; i++) {
        if (keyword[i] >= 'A' && keyword[i] <= 'Z') {
            keyAlphabet[k++] = keyword[i];
        }
    }
    
    // Fill keyAlphabet with remaining letters of the alphabet
    for (i = 'A'; i <= 'Z'; i++) {
        if (!strchr(keyword, i)) {
            keyAlphabet[k++] = i;
        }
    }
    
    // Input plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the newline character
    
    // Encrypt the plaintext
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            // Determine position in the alphabet
            int pos = toupper(plaintext[i]) - 'A';
            // Encrypt using the keyAlphabet
            ciphertext[i] = isupper(plaintext[i]) ? keyAlphabet[pos] : tolower(keyAlphabet[pos]);
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }
    ciphertext[i] = '\0'; // Null-terminate the ciphertext
    
    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}

