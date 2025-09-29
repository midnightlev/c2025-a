#include <stdio.h>
#include <string.h>

void encrypt(const char* input, char* output) {
    const int key = 0b110000111111111111;

    for (int i = 0; i < strlen(input); i++) {
        output[i] = input[i] ^ key;
    }
    output[strlen(input)] = '\0';
}

void decrypt(const char* input, char* output) {
    encrypt(input, output);
}

int main() {
    char input[500];
    char encrypted[500];
    char decrypted[500];

    printf("Input: ");
    scanf("%499s", input);

    // encrypt
    encrypt(input, encrypted);
    printf("Encrypted: %s\n", encrypted);

    // decrypt
    decrypt(encrypted, decrypted);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}