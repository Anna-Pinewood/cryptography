#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
int main()
{
    FILE *MESSAGE;
    MESSAGE = fopen("message.txt","r");
    char *buf;
    fseek(MESSAGE, 0, SEEK_END);
    long size = ftell(MESSAGE);
    buf = malloc(size*sizeof(char));
    if (buf == NULL) {
        printf(stderr, "Memory mistake");
        return 1;
    }
    int rc;
    for (int i = 0; (rc=getc(MESSAGE)) != EOF && i < size; buf[i++] = rc);
for (int i = 0; i < size; i++) printf("buf[%d] = %d \n", i ,buf[i]);
return 0;
}