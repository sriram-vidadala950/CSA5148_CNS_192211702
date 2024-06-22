#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the Playfair key matrix from the given key
void prepare_key_matrix(char keyMatrix[5][5], char *key) {
    int len = strlen(key);
    int index = 0;
    int i, j;
    char alphabet[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    
    // Process the key (replace J with I and remove duplicates)
    for (i = 0; i < len; i++) {
        key[i] = toupper(key[i]);
        if (key[i] == 'J') key[i] = 'I'; // 'J' and 'I' are considered the same in Playfair cipher
    }
    
    // Remove duplicates from the key
    int exists[26] = {0};
    for (i = 0; i < len; i++) {
        if (key[i] != ' ' && exists[key[i] - 'A'] == 0) {
            exists[key[i] - 'A'] = 1;
            key[index++] = key[i];
        }
    }
    key[index] = '\0';
    
    // Fill the key matrix with the key
    index = 0;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (index < strlen(key)) {
                keyMatrix[i][j] = key[index++];
            } else {
                // Fill remaining matrix with remaining alphabet
                while (exists[alphabet[index] - 'A'] == 1) index++; // Skip used letters
                keyMatrix[i][j] = alphabet[index++];
            }
        }
    }
}

// Function to encrypt using Playfair cipher
void encrypt_playfair(char *plaintext, char keyMatrix[5][5]) {
    int len = strlen(plaintext);
    char ciphertext[len * 2]; // Maximum possible length of ciphertext
    int index = 0;
    int i, j;
    
    // Adjust plaintext (double letters and add filler 'X' if necessary)
    for (i = 0; i < len; i++) {
        plaintext[i] = toupper(plaintext[i]);
        if (plaintext[i] == 'J') plaintext[i] = 'I'; // Treat 'J' as 'I'
        if (!isalpha(plaintext[i])) continue;
        if (i < len - 1 && plaintext[i] == plaintext[i + 1]) {
            // If consecutive letters are the same, insert a filler character
            if (plaintext[i] == 'X') plaintext[i + 1] = 'Q'; // Avoid 'Q' being the next character
            else plaintext[i + 1] = 'X';
            len++; // Increase length due to insertion
        }
    }
    
    // Encrypt the plaintext
    for (i = 0; i < len; i += 2) {
        char letter1 = plaintext[i];
        char letter2 = (i + 1 < len) ? plaintext[i + 1] : 'X'; // Use 'X' as filler if odd number of characters
        
        int row1, col1, row2, col2,k;
        
        // Find positions of the two letters in the key matrix
        for (j = 0; j < 5; j++) {
            for ( k = 0; k < 5; k++) {
                if (keyMatrix[j][k] == letter1) {
                    row1 = j;
                    col1 = k;
                }
                if (keyMatrix[j][k] == letter2) {
                    row2 = j;
                    col2 = k;
                }
            }
        }
        
        if (row1 == row2) {
            // Same row
            ciphertext[index++] = keyMatrix[row1][(col1 + 1) % 5];
            ciphertext[index++] = keyMatrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column
            ciphertext[index++] = keyMatrix[(row1 + 1) % 5][col1];
            ciphertext[index++] = keyMatrix[(row2 + 1) % 5][col2];
        } else {
            // Rectangle rule
            ciphertext[index++] = keyMatrix[row1][col2];
            ciphertext[index++] = keyMatrix[row2][col1];
        }
    }
    
    ciphertext[index] = '\0'; // Null-terminate the ciphertext
    
    // Output the encrypted message
    printf("Encrypted message: %s\n", ciphertext);
}

int main() {
    char keyMatrix[5][5] = {0}; // Playfair key matrix
    char key[] = "MFHIK UNOPQ ZVWXY ELARG"; // Example key matrix
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    
    // Prepare the Playfair key matrix
    prepare_key_matrix(keyMatrix, key);
    
    // Encrypt the message using Playfair cipher
    encrypt_playfair(plaintext, keyMatrix);
    
    return 0;
}

