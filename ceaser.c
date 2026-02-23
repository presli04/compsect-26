#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // за isupper()

char caesar_encrypt_char(char p, int k) {
if (isupper(p)) {
return ( (p - 'A' + k) % 26 ) + 'A';
}
else if(islower(p))
{
    return ( (p - 'A' + k) % 26 ) + 'A';
}
return p; // Ако не е буква (напр. цифра), връщаме без промяна
}

char caesar_decrypt_char(char c, int k) {
if (isupper(c)) {
return ((c - 'A' - k + 26)%26) + 'A';
}
else if(islower(c))
{
    return((c - 'A' - k +26)%26) + 'A';
}
return c;
}
void apply_cypher(char *text,int key)
{
    for (int i=0;text[i]!='\0';i++)
    {
         text[i]=caesar_decrypt_char(text[i],key);
    }
    
}
void apply_decypher(char *text,int key)
{
    for (int i=0;text[i]!='\0';i++)
    {
        text[i]=caesar_decrypt_char(text[i],key);
    }
}
int main()
{
    char text[]="Hello";
    int key=3;
    
    printf("Original: %s\n",text);
    apply_cypher(text,key);
    printf("Encrypted: %s\n",text);
    apply_decypher(text,key);
    printf("Decrypted: %s\n",text);
    return 0;
    
}   