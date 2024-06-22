#include <stdio.h>
#include <string.h>

int main() {
    char ciphertext[] = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83"
                        "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8*"
                        ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81"
                        "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";
    
    char plaintext[500]; // Assuming sufficient size for the plaintext
    int i;

    // Mapping table based on frequency analysis and common words in English
    char mapping[256];
    memset(mapping, 0, sizeof(mapping)); // Initialize mapping table
    
    // Manual mapping based on frequency and common words analysis
    mapping['5'] = 'I';
    mapping['3'] = 'T';
    mapping['†'] = ' ';
    // Add more mappings based on the analysis...

    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];
        if (mapping[c] != '\0') {
            plaintext[i] = mapping[c];
        } else {
            plaintext[i] = c; // Copy non-mapped characters as is
        }
    }
    plaintext[i] = '\0'; // Null-terminate the plaintext string

    printf("Decrypted text:\n%s\n", plaintext);

    return 0;
}

