#include "Hash.h"



int main() {
    unsigned char hexArray[ARRAY_SIZE];
    unsigned char hash[HASH_SIZE];

    srand(time(NULL));

    generateRandomHexArray(hexArray);
    calculateHash(hexArray, hash);

    PrintArray(hexArray);

    printf("Initial Hash: ");
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x  ", hash[i]);
    }
    printf("\n");

    // Modify one byte in the hexArray
    int indexToChange = rand() % ARRAY_SIZE;
    hexArray[indexToChange] = rand() % 256;

    unsigned char newHash[HASH_SIZE];
    calculateHash(hexArray, newHash);

    printf("New Hash after modifying index %d: ", indexToChange);
    for (int i = 0; i < HASH_SIZE; ++i) {
        printf("%02x  ", newHash[i]);
    }
    printf("\n");

    return 0;
}
