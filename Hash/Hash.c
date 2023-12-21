
#include "Hash.h"
/****************************************************************************/
void generateRandomHexArray(unsigned char hexArray[]) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        hexArray[i] = rand() % 256; // Generate a random number between 0 and 255
    }
}
/****************************************************************************/

void calculateHash(const unsigned char hexArray[], unsigned char hash[]) {
    for (int i = 0; i < HASH_SIZE; ++i) {
        hash[i] = i; // Initialize each byte of the hash with its index value
        for (int j = 0; j < ARRAY_SIZE; ++j) {
            hash[i] = (hash[i] ^ hexArray[j])  ; // Mix each byte of the hash with the array
        }
    }
}
/****************************************************************************/
void PrintArray(unsigned char hexArray[]){

 printf(" The Array :");
 for (int i = 0; i < ARRAY_SIZE; ++i) {
        printf(" %d  ", hexArray[i]);
    }
    printf("\n");
    printf("\n");
}
/****************************************************************************/
