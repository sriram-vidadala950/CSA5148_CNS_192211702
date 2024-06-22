#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
int main() {
    char key[26];
    char plaintext[256];
    char preparedText[256];
    char ciphertext[256];
    char keySquare[5][5];
    int alpha[26] = {0};
    int i, j, k, len;
    int pos[4];
    // Input key from the user
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove the trailing newline character
    // Prepare key by converting to uppercase and removing non-alphabet characters
    k = 0;
    for (i = 0; key[i] != '\0'; i++) {
        if (isalpha(key[i])) {
            key[k++] = toupper(key[i]);
        }
    }
    key[k] = '\0';
    // Generate the key square
    k = 0;
    for (i = 0; i < strlen(key); i++) {
        if (key[i] == 'J') key[i] = 'I'; // Replace 'J' with 'I'
        if (alpha[key[i] - 'A'] == 0) {
            keySquare[k / 5][k % 5] = key[i];
            alpha[key[i] - 'A'] = 1;
            k++;
        }
    }
    for (i = 0; i < 26; i++) {
        if (i + 'A' == 'J') continue; // Skip 'J'
        if (alpha[i] == 0) {
            keySquare[k / 5][k % 5] = i + 'A';
            k++;
        }
    }
    // Input plaintext from the user
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove the trailing newline character
    // Prepare plaintext by converting to uppercase and removing non-alphabet characters
    k = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            preparedText[k++] = toupper(plaintext[i]);
        }
    }
    preparedText[k] = '\0';
    // Encrypt the plaintext
    len = strlen(preparedText);
    for (i = 0; i < len; i += 2) {
        if (i + 1 == len || preparedText[i] == preparedText[i + 1]) {
            // If only one character remains or characters are the same, add filler 'X'
            preparedText[len] = 'X';
            preparedText[len + 1] = '\0';
            len++;
        }
        // Search for the positions of the two letters in the key square
        for (j = 0; j < 4; j++) pos[j] = -1;
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (keySquare[j][k] == preparedText[i]) {
                    pos[0] = j;
                    pos[1] = k;
                }
                if (keySquare[j][k] == preparedText[i + 1]) {
                    pos[2] = j;
                    pos[3] = k;
                }
            }
        }
        if (pos[0] == pos[2]) {
            // Same row
            ciphertext[i] = keySquare[pos[0]][(pos[1] + 1) % 5];
            ciphertext[i + 1] = keySquare[pos[2]][(pos[3] + 1) % 5];
        } else if (pos[1] == pos[3]) {
            // Same column
            ciphertext[i] = keySquare[(pos[0] + 1) % 5][pos[1]];
            ciphertext[i + 1] = keySquare[(pos[2] + 1) % 5][pos[3]];
        } else {
            // Rectangle
            ciphertext[i] = keySquare[pos[0]][pos[3]];
            ciphertext[i + 1] = keySquare[pos[2]][pos[1]];
        }
    }
    ciphertext[len] = '\0'; // Null-terminate the ciphertext
    // Output the ciphertext
    printf("Ciphertext: %s\n", ciphertext);
    return 0;
}

