#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#include <openssl/err.h>

#define BUFFER_SIZE 4096

void handle_errors() {
    ERR_print_errors_fp(stderr);
    exit(1);
}


void derive_key(const char *password, unsigned char *key) {
    SHA256((unsigned char*)password, strlen(password), key);
}

void process_file(const char *in_filename, const char *out_filename, 
                  unsigned char *key, unsigned char *iv, int do_encrypt) {
    FILE *in = fopen(in_filename, "rb");
    FILE *out = fopen(out_filename, "wb");
    if (!in || !out) {
        perror("Грешка при отваряне на файл");
        exit(1);
    }

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    if (!ctx) handle_errors();

    
    if (1 != EVP_CipherInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv, do_encrypt))
        handle_errors();

    unsigned char in_buf[BUFFER_SIZE];
    unsigned char out_buf[BUFFER_SIZE + EVP_MAX_BLOCK_LENGTH];
    int in_len, out_len;

    
    while ((in_len = fread(in_buf, 1, BUFFER_SIZE, in)) > 0) {
        if (1 != EVP_CipherUpdate(ctx, out_buf, &out_len, in_buf, in_len))
            handle_errors();
        fwrite(out_buf, 1, out_len, out);
    }

    
    if (1 != EVP_CipherFinal_ex(ctx, out_buf, &out_len)) {
        fprintf(stderr, "Грешка при финализиране (вероятно грешен ключ или повреден файл).\n");
        exit(1);
    }
    fwrite(out_buf, 1, out_len, out);

    EVP_CIPHER_CTX_free(ctx);
    fclose(in);
    fclose(out);
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        fprintf(stderr, "Употреба: %s [enc|dec] input_file output_file key_string\n", argv[0]);
        return 1;
    }

    char *mode = argv[1];
    char *input_path = argv[2];
    char *output_path = argv[3];
    char *password = argv[4];

    int do_encrypt = (strcmp(mode, "enc") == 0);
    if (!do_encrypt && strcmp(mode, "dec") != 0) {
        fprintf(stderr, "Грешен режим! Използвайте 'enc' или 'dec'.\n");
        return 1;
    }

    unsigned char key[32];
    unsigned char iv[16] = {0}; 

    derive_key(password, key);

    printf("%s: %s -> %s...\n", do_encrypt ? "Криптиране" : "Декриптиране", input_path, output_path);
    
    process_file(input_path, output_path, key, iv, do_encrypt);

    printf("Готово!\n");

    return 0;
}