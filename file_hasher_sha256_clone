#include <stdio.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 1024 

void calculate_sha256(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Грешка при отваряне на файла");
        return;
    }

    EVP_MD_CTX *mdctx = EVP_MD_CTX_new();
    if (mdctx == NULL) {
        fclose(file);
        fprintf(stderr, "Грешка при създаване на контекст.\n");
        return;
    }

    
    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        fprintf(stderr, "Грешка при инициализация на Digest.\n");
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        return;
    }

    unsigned char buffer[BUFFER_SIZE];
    size_t bytes_read;

    
    
    while ((bytes_read = fread(buffer, 1, BUFFER_SIZE, file)) != 0) {
        if (1 != EVP_DigestUpdate(mdctx, buffer, bytes_read)) {
            fprintf(stderr, "Грешка при обновяване на Digest.\n");
            EVP_MD_CTX_free(mdctx);
            fclose(file);
            return;
        }
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;

    
    if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
        fprintf(stderr, "Грешка при финализиране на Digest.\n");
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        return;
    }

    
    printf("SHA256(%s) = ", filename);
    for (unsigned int i = 0; i < hash_len; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    
    EVP_MD_CTX_free(mdctx);
    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Употреба: %s <име_на_файл>\n", argv[0]);
        return 1;
    }

    calculate_sha256(argv[1]);

    return 0;
}