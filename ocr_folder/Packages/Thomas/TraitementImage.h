//
// Created by root on 18/10/18.
//

#ifndef PROJECT2_TRAITEMENTIMAGE_H
#define PROJECT2_TRAITEMENTIMAGE_H

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <math.h>
#include <string.h>


typedef struct {
    short bftype;
    int bfSize;
    short bfReserved1;
    short bfReserved2;
    int bfOffBits;
    int biSize;
    int biWidth;
    int biHeight;
    short biPlanes;
    short biBitCount;
    int biCompression;
    int biSizeImage;
    int biXpelsPerMeter;
    int biYpelsPerMeter;
    int biClrUsed;
    int biClrImportant;
} BITMAPHEADER;

typedef struct {
    unsigned char R;
    unsigned char V;
    unsigned char B;
    unsigned char Gris;
    int yes;
} Pixel_;

typedef struct {
    BITMAPHEADER header;
    size_t height;
    size_t width;
    unsigned char *HEADERDATA;
    unsigned char *PIXELDATA;
    unsigned char **GREYMATRIX;
    
    unsigned char **TEXTZONE;

    size_t* colons_scope;
    int last;
} BMPPic_;

BMPPic_ treatPic(FILE *file);
BMPPic_ setPixel(BMPPic_ myPic,size_t i,size_t j,Pixel_ pixel);
Pixel_ getPixel(BMPPic_ myPic,size_t i,size_t j);
BMPPic_ getHeader(char data[]);
BMPPic_ Init(FILE *file, BMPPic_ myPic);
BMPPic_ InitGreyMatr(BMPPic_ myPic);
BMPPic_ setGray(BMPPic_ myPic,size_t x, size_t y,unsigned char val);
unsigned char getGray(BMPPic_ myPic,size_t x, size_t y);
void restructPic(BMPPic_ myPic, char name[]);
BMPPic_ ApplyRLSA(BMPPic_ myPic,int seuil_a,int seuil_b);

#endif //PROJECT2_TRAITEMENTIMAGE_H