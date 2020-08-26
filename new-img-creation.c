#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MESSAGE "message.txt"
//#include <stdafx.h>
#include <windows.h>
#pragma pack(push, 1)
typedef struct{
    WORD    bfType;
    DWORD   bfSize;
    WORD    bfReserved1;
    WORD    bfReserved2;
    DWORD   bfOffBits;
} TBITMAPFILEHEADER;
typedef struct {
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
} TBITMAPINFOHEADER;
typedef struct {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
} RGB;
#pragma pack(pop)

void show_bitmapfileheader(TBITMAPFILEHEADER* header){
    printf("---BITMAPFILEHEADER---\n");
    printf("-bfType          %04x-\n", header->bfType); // 4D42 for BMP
    printf("-bfSize    %10ld-\n", header->bfSize);
    printf("-bfReserved1     %4hu-\n", header->bfReserved1);
    printf("-bfReserved2     %4hu-\n", header->bfReserved2);
    printf("-bfOffBits      %5ld-\n", header->bfOffBits);
    printf("---------END----------\n \n");
};
void show_bitmapinfoheader(TBITMAPINFOHEADER* header){
    printf("---BITMAPINFOHEADER---\n");
    printf("-biSize                 %ld-\n", header->biSize); // 4D42 for BMP
    printf("-biWidth                      %ld-\n", header->biWidth);
    printf("-biHeight               %ld-\n", header->biHeight);
    printf("-biPlanes                     %hu-\n", header->biPlanes);
    printf("-biBitCount                   %hu-\n", header->biBitCount);
    printf("-biCompression       %ld-\n", header->biCompression);
    printf("-biSizeImage         %ld-\n", header->biSizeImage);
    printf("-biXPerMeter         %ld-\n", header->biXPelsPerMeter);
    printf("-biYPelsPerMeter     %ld-\n", header->biYPelsPerMeter);
    printf("-biClrUsed           %ld-\n", header->biClrUsed);
    printf("-biClrImportant      %ld-\n", header->biClrImportant);

    printf("---------END----------\n");
};
void show_rgbtriple(RGB* header) {
    printf("---RGBTRIPLE---\n");
    printf("-rgbtRed      %d-\n", header->rgbtRed);
    printf("-rgbtGreen    %d-\n", header->rgbtGreen);
    printf("-rgbtBlue     %d-\n", header->rgbtBlue);
    printf("---------END----------\n");

}
void read_text(unsigned char *buf) {
    FILE *message = fopen(MESSAGE, "r");
    fseek(message, 0, SEEK_END);
    long size = ftell(message);
    fseek(message, 0, SEEK_SET);
    buf = malloc(size * sizeof(unsigned char));
    if (buf == NULL) {
        fprintf(stderr, "Error! Not enough memory.\n");
        exit(1);
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

}
int main(){
    unsigned char *buf_text = NULL;
    read_text(buf_text);

    FILE *IMG = fopen("img.bmp", "rb");
    TBITMAPFILEHEADER* header1 = (TBITMAPFILEHEADER*) malloc (sizeof(TBITMAPFILEHEADER));
    TBITMAPINFOHEADER* header2 = (TBITMAPINFOHEADER*) malloc (sizeof(TBITMAPINFOHEADER));
    RGB* header3 = (RGB*) malloc (sizeof(RGB));
    if (header1 != NULL) {
        fread(header1, sizeof(BITMAPFILEHEADER), 1, IMG);
        show_bitmapfileheader(header1);
        }
    if (header2 != NULL) {
        fread(header2, sizeof(BITMAPINFOHEADER), 1, IMG);
        show_bitmapinfoheader(header2);
        }
    int i;
    int len = header2->biWidth * header2->biHeight;
    RGB *buf_pix = NULL;
    buf_pix = malloc(len * sizeof(RGB));
    if (buf_pix == NULL) {
        fprintf(stderr, "Error! Not enough memory.\n");
        }
    else{
        for (i=0; i<len; i++) {
            //printf("i = %d \n", i);
            fread(header3, sizeof(RGB), 1, IMG);
            buf_pix[i].rgbtRed = header3->rgbtRed;
            buf_pix[i].rgbtGreen = header3->rgbtGreen;
            buf_pix[i].rgbtBlue = header3->rgbtBlue;
           // show_rgbtriple(header3);
        }
        }
    fclose(IMG);
    int width = header2->biWidth;
    int height = header2->biHeight;
    FILE *IMG_NEW = fopen("img_new.bmp", "w");
    fwrite(header1, 1, sizeof(header1), IMG_NEW);
    fwrite(header2, 1, sizeof(header2), IMG_NEW);
    for (int i =0; i<(sizeof(buf_text)/sizeof(buf_text[0])); i++) {
        buf_pix->rgbtBlue = buf_text[i];
    }
   // int f = 0;
    int size = sizeof(RGB);
    char *c;
    c = (char*)buf_pix;
    for (int i=0; i<height; i++) {
        for (int j=0; j<width; j++) {
            for (int f=0; f<size; f++){
                putc(*c++, IMG_NEW);
            }
        }
    }

    return 0;
}