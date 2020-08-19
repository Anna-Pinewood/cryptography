

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <wingdi.h>
/*typedef struct tagBITMAPINFOHEADER
{
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
} BITMAPINFOHEADER, *PBITMAPINFOHEADER;

   typedef struct tagRGBTRIPLE {
    BYTE rgbtBlue;
    BYTE rgbtGreen;
    BYTE rgbtRed;
  } RGBTRIPLE;*/
int main(){
    int i, j;
    FILE * IMG = fopen("img.BMP", "rb");
    BITMAPFILEHEADER  header1;
    PBITMAPFILEHEADER * ptr_header1;
    BITMAPINFOHEADER  header2;
    PBITMAPINFOHEADER * ptr_header2;
    RGBTRIPLE rgb;
    fseek(IMG, 392, SEEK_SET);
    fread(header2.biWidth, sizeof(int), 1, IMG);
    fread(header2.biHeight, sizeof(int), 1, IMG);
    int buf_size = header2.biWidth*header2.biHeight;
    RGBTRIPLE buf[buf_size]; // ???
    fseek(IMG, 10, SEEK_SET);
    fread(header1.bfOffBits, sizeof(DWORD), 1, IMG);
    fseek(IMG, 10, SEEK_SET);
    for (i=0; i < buf_size; i++) {
        for (j=0; j<3; j++) {
            if (j==0)  fread(rgb.rgbtRed, sizeof(BYTE), 1, IMG);
            else if (j==1) fread(rgb.rgbtGreen, sizeof(BYTE), 1, IMG);
            else fread(rgb.rgbtBlue, sizeof(BYTE), 1, IMG);
            RGBTRIPLE temp[1] = {rgb};
        }
        memcpy(buf, &rgb, sizeof(RGBTRIPLE));
    }
  /* for (i=0; i<buf_size; i++){
        for (j=0; j<3; j++) {
            if (j==0)  printf("%d", rgb.rgbtRed);
            else if (j==1) printf("%d", rgb.rgbtGreen);
            else printf("%d", rgb.rgbtBlue);
        }
    }*/
    fclose(IMG);

    return 0;
}