#include <stdio.h>
#include <malloc.h>
#include "CRYPTOGRAPHY.h"
#define MESSAGE "message.txt"

int main(){
//    test function show_binary_representation
//    unsigned char value;
//    scanf("%c", &value);
//    show_binary_representation(value);
    FILE *message = fopen(MESSAGE, "r");
    fseek(message, 0, SEEK_END);
    long size = ftell(message);
    fseek(message, 0, SEEK_SET);
    unsigned char *buf = NULL;
    buf = malloc(size * sizeof(unsigned char));
    if (buf == NULL) {
        fprintf(stderr, "Error! Not enough memory.\n");
        return 1;
    }
    else{
        unsigned char rc;
        for (int i = 0; i < size; i++){
            rc=getc(message);
            buf[i] = rc;
            printf("\nbuf[%d] = %d %c\n", i ,buf[i], buf[i]);
        };
    }
    fclose(message);
    return 0;
}