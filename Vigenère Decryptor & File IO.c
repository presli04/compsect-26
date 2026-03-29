#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void vigenere_decrypt(const char *ciphertext, const char *key, char *output) {
    int key_len = strlen(key);
    if (key_len == 0) return; 

    int key_index = 0;
    int i;

    for (i = 0; ciphertext[i] != '\0'; i++) {
        char c = ciphertext[i];

        if (isalpha(c)) {
            
            char base = isupper(c) ? 'A' : 'a';
            char k_char = toupper(key[key_index % key_len]);
            int shift = k_char - 'A';

            
            output[i] = ((toupper(c) - 'A' - shift + 26) % 26) + 'A';
            
            
            if (islower(c)) output[i] = tolower(output[i]);
            
            key_index++;
        } else {
            output[i] = ciphertext[i];
        }
    }
    output[i] = '\0'; 
}

int main() {
    
    FILE *fin = fopen("encrypted.txt", "r");
    FILE *fkey = fopen("key.txt", "r");
    FILE *fout = fopen("decrypted.txt", "w");

    
    if (!fin || !fkey || !fout) {
        printf("Error opening file(s).\n");
        if (fin) fclose(fin);
        if (fkey) fclose(fkey);
        
        return 1;
    }

    char ciphertext[10000];
    char key[1000];
    char output[10000];

    
    if (fgets(ciphertext, sizeof(ciphertext), fin)) {
        ciphertext[strcspn(ciphertext, "\r\n")] = '\0'; 
    }
    if (fgets(key, sizeof(key), fkey)) {
        key[strcspn(key, "\r\n")] = '\0'; 
    }

    vigenere_decrypt(ciphertext, key, output);

    fprintf(fout, "%s", output);

    fclose(fin);
    fclose(fkey);
    fclose(fout);

    printf("Decryption completed. Result saved in decrypted.txt\n");
    return 0;
}