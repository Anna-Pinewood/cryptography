#include <stdio.h>
#include <windows.h>

#pragma pack(push, 1)
typedef struct{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} TBITMAPFILEHEADER;
#pragma pack(pop)

void show_bitmapfileheader(TBITMAPFILEHEADER* header){
    printf("---BITMAPFILEHEADER---\n");
    printf("-bfType          %04x-\n", header->bfType); // 4D42 for BMP
    printf("-bfSize    %10ld-\n", header->bfSize);
    printf("-bfReserved1     %4hu-\n", header->bfReserved1);
    printf("-bfReserved2     %4hu-\n", header->bfReserved2);
    printf("-bfOffBits      %5ld-\n", header->bfOffBits);
    printf("---------END----------\n");
};

int main(){
    FILE *IMG = fopen("img.bmp", "rb");
    TBITMAPFILEHEADER* header1 = (TBITMAPFILEHEADER*) malloc (sizeof(TBITMAPFILEHEADER));
    if (header1 != NULL) {
        fread(header1, sizeof(BITMAPFILEHEADER), 1, IMG);
        show_bitmapfileheader(header1);
    }
    fclose(IMG);
    return 0;
}