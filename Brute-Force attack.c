#include <stdio.h>
#include <ctype.h>
#include <string.h>

char decrypt_char(char c, int key) {
   
    int shift = key % 26;
    
    if (c >= 'A' && c <= 'Z') {
        return 'A' + (c - 'A' - shift + 26) % 26;
    }
    if (c >= 'a' && c <= 'z') {
        return 'a' + (c - 'a' - shift + 26) % 26;
    }
    return c; 
}


void decrypt_with_key(const char *text, int key) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        putchar(decrypt_char(text[i], key));
    }
    putchar('\n');
}

int main(int argc, char *argv[]) { 
    int key;

    if (argc != 2) {
      
        printf("Usage: %s \"encrypted text\"\n", argv[0]);
        return 1;
    }

    printf("Trying all 25 possible Caesar cipher shifts:\n\n");

    for (key = 1; key <= 25; key++) {
        printf("Key %2d: ", key);
        decrypt_with_key(argv[1], key); 
    }

    return 0;
}