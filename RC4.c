#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STATE_SIZE 256

void rc4_init(unsigned char *S, const unsigned char *key, int key_len) {
for (int i = 0; i < STATE_SIZE; i++) {
S[i] = i;
}

int j = 0;
for (int i = 0; i < STATE_SIZE; i++) {
j = (j + S[i] + key[i % key_len]) % STATE_SIZE;

unsigned char temp = S[i];
S[i] = S[j];
S[j] = temp;
}
}

void rc4_crypt(unsigned char *data, long data_len, const unsigned char *key, int key_len) {
unsigned char S[STATE_SIZE];
rc4_init(S, key, key_len);

int i = 0, j = 0;

for (long n = 0; n < data_len; n++) {
i = (i + 1) % STATE_SIZE;
j = (j + S[i]) % STATE_SIZE;

unsigned char temp = S[i];
S[i] = S[j];
S[j] = temp;

int K = S[(S[i] + S[j]) % STATE_SIZE];
data[n] ^= K;
}
}

int main(int argc, char *argv[]) {
if (argc != 4) {
printf("Usage: %s <input_file> <output_file> <password>\n", argv[0]);
return 1;
}

const char *input_filename = argv[1];
const char *output_filename = argv[2];
const unsigned char *password = (unsigned char *)argv[3];
int password_len = strlen((const char *)password);

if (password_len == 0) {
printf("Error: password must not be empty.\n");
return 1;
}

FILE *infile = fopen(input_filename, "rb");
if (!infile) {
perror("Error opening input file");
return 1;
}

fseek(infile, 0, SEEK_END);
long file_size = ftell(infile);
rewind(infile);

if (file_size < 0) {
printf("Error determining file size.\n");
fclose(infile);
return 1;
}

unsigned char *buffer = (unsigned char *)malloc(file_size);
if (!buffer) {
printf("Memory allocation error.\n");
fclose(infile);
return 1;
}

size_t bytes_read = fread(buffer, 1, file_size, infile);
fclose(infile);

if (bytes_read != (size_t)file_size) {
printf("Error reading input file.\n");
free(buffer);
return 1;
}

rc4_crypt(buffer, file_size, password, password_len);

FILE *outfile = fopen(output_filename, "wb");
if (!outfile) {
perror("Error opening output file");
free(buffer);
return 1;
}

size_t bytes_written = fwrite(buffer, 1, file_size, outfile);
fclose(outfile);
free(buffer);

if (bytes_written != (size_t)file_size) {
printf("Error writing output file.\n");
return 1;
}

printf("Done. Output written to %s\n", output_filename);
return 0;
}