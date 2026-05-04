#include <stdio.h>
#include<string.h>
#include <openssl/sha.h>

void sha256_hash(const char *input,char *output)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,input,strlen(input));
    SHA256_Final(hash,&sha256);

    for(int i=0;i<SHA256_DIGEST_LENGTH;i++)
    {
        sprintf(output+(i*2),"%02x",hash[i]);

    }
    output[64]="\0";

}

int main()
{
    const char *target_hash="ef797c8118f02dfb649607dd5d3f8c7623048c9c063d532cc95c5ed7a898a64f";
    char salt[]="2026-";
    char attempt[11];
    char current_hash[65];
    for(int i=0;i<=9999;i++)
    {
        sprintf(attempt,"%s%04d",salt,i);
        sha256_hash(attempt,current_hash);
        if(strcmp(current_hash,target_hash)==0)
        {
            printf("\nSuccess");
            printf("Full string: %s\n",attempt);
            printf("PIN: %04d\n",i);
            return 0;
        }
    }

    return 0;
}