#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define HASH_SIZE 16
#define ARRAY_SIZE 256



void generateRandomHexArray(unsigned char hexArray[]);

void calculateHash(const unsigned char hexArray[], unsigned char hash[]);

void PrintArray(unsigned char hexArray[]);
