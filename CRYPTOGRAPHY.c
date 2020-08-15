#include <stdio.h>
#include "CRYPTOGRAPHY.h"

// little-endian format
void show_binary_representation(unsigned char symbol){
    unsigned int array_of_bits[8];
    fprintf(stdout ,"Symbol is %c : %d\n", symbol, symbol);
    for (int i = 0; i < 8; i++) {
        if ((symbol & (1 << i)) == 0) {
            array_of_bits[i] = 0;
        }
        else {
            array_of_bits[i] = 1;
        }
        printf("%d", array_of_bits[i]);
    }
    printf("\n");
};
