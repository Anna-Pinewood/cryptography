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
    printf("-rgbtRed      %b-\n", header->rgbtRed);
    printf("-rgbtGreen    %b-\n", header->rgbtGreen);
    printf("-rgbtBlue     %b-\n", header->rgbtBlue);
    printf("---------END----------\n");

}
int main(){
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
  //  int len = header2->biWidth * header2->biHeight;
    for (i=0; i<768432; i++) {
        printf("i = %d \n", i);
        fread(header3, sizeof(RGB), 1, IMG);
        show_rgbtriple(header3);
    }
    fclose(IMG);
    return 0;
}