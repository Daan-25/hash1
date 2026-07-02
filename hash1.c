#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Use: ./hash1 <filename>\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "rb");
    if (!file) {
        printf("Error: Can't open file '%s'\n", argv[1]);
        return 1;
    }

    SHA_CTX context;
    SHA1_Init(&context);

    unsigned char buffer[8192];
    size_t bytes_read;

    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        SHA1_Update(&context, buffer, bytes_read);
    }

    fclose(file);

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &context);

    printf("SHA-1 hash from %s:\n", argv[1]);
    for (int i = 0; i < SHA_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    return 0;
}