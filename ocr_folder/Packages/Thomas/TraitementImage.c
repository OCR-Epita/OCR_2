//
// Created by root on 18/10/18.
//

#include <stdlib.h>
#include <stdio.h>
#include "../lucas/Binary.h"

#include "TraitementImage.h"

BMPPic_ getHeader(char data[]){
    BMPPic_ myPic;
    myPic.header.bftype = *((short *) (data + 0));
    myPic.header.bfSize = *((int *) (data + 2));
    myPic.header.bfReserved1 = *((short *) (data + 6));
    myPic.header.bfReserved2 = *((short *) (data + 8));
    myPic.header.bfOffBits = *((char *) (data + 10));
    myPic.header.biSize = *((int *) (data + 14));
    myPic.header.biSize = *((int *) (data + 14));
    myPic.header.biSize = *((int *) (data + 14));
    myPic.header.biWidth = *((int *) (data + 18));
    myPic.header.biHeight = *((int *) (data + 22));
    myPic.header.biSize = *((short *) (data + 26));
    myPic.header.biBitCount = *((short *) (data + 28));
    myPic.header.biCompression = *((int *) (data + 30));
    myPic.header.biSizeImage = *((int *) (data + 34));
    myPic.header.biXpelsPerMeter = *((int *) (data + 38));
    myPic.header.biYpelsPerMeter = *((int *) (data + 42));
    myPic.header.biClrUsed = *((int *) (data + 46));
    myPic.header.biClrImportant = *((int *) (data + 50));
    return myPic;
}

BMPPic_ Init(FILE *file, BMPPic_ myPic){
    char firstRead[128];
    fread(firstRead, 128, 1, file);
    myPic = getHeader(firstRead);
    myPic.height = (size_t) myPic.header.biHeight;
    myPic.width = (size_t) myPic.header.biWidth;
    fseek(file,0,SEEK_SET);
    myPic.HEADERDATA = calloc((size_t) myPic.header.bfOffBits, sizeof(char));
    fread(myPic.HEADERDATA,(size_t) myPic.header.bfOffBits,1,file);
    fseek(file,myPic.header.bfOffBits,SEEK_SET);
    myPic.PIXELDATA = calloc((size_t) myPic.header.bfSize - myPic.header.bfOffBits, sizeof(char));
    fread(myPic.PIXELDATA,(size_t) myPic.header.bfSize - myPic.header.bfOffBits,1,file);

    myPic = InitGreyMatr(myPic);

    return myPic;
}

BMPPic_ InitGreyMatr(BMPPic_ myPic){
    myPic.GREYMATRIX = malloc(myPic.height*myPic.width*sizeof(char));
    for (int i = 0; i < myPic.height; ++i) {
        myPic.GREYMATRIX[i]=malloc(myPic.width* sizeof(char));
        for (int j = 0; j < myPic.width; ++j) {
            Pixel_ tp = getPixel(myPic,i,j);
            unsigned char a = (tp.B + tp.V + tp.R) / 3;
            myPic.GREYMATRIX[i][j]=a;
            /*Pixel_ p;
            p.R = a;
            p.V = a;
            p.B = a;
            myPic = setPixel(myPic,i,j,p);*/
        }
    }

    return myPic;
}

Pixel_ getPixel(BMPPic_ myPic,size_t i,size_t j){
    Pixel_ cur;
    cur.R = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 0];
    cur.V = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 1];
    cur.B = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 2];
    return cur;
}

BMPPic_ setPixel(BMPPic_ myPic,size_t i,size_t j,Pixel_ pixel){
    if(i >= myPic.height || j >= myPic.width)
        err(1,"ERREUR: setpixel arg i et j");
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 0] = pixel.R;
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 1] = pixel.V;
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 2] = pixel.B;
    return myPic;
}

unsigned char getGray(BMPPic_ myPic,size_t x, size_t y){
    unsigned char res = 0;
    if(x >= 0 && x < myPic.height && y >= 0 && y < myPic.width)
        res = myPic.GREYMATRIX[x][y];
    return res;
}

BMPPic_ setGray(BMPPic_ myPic,size_t x, size_t y,unsigned char val){
    myPic.GREYMATRIX[x][y] = val;
    return myPic;
}

void restructPic(BMPPic_ myPic){
    for (int i = 0; i < myPic.height; ++i) {
        for (int j = 0; j < myPic.width; ++j) {
            Pixel_ cur;
            cur.R = myPic.GREYMATRIX[i][j];
            cur.V = myPic.GREYMATRIX[i][j];
            cur.B = myPic.GREYMATRIX[i][j];
            myPic = setPixel(myPic,i,j,cur);
        }
    }
    FILE *ok;
    ok = fopen("../retouche.bmp","w+");
    fwrite(myPic.HEADERDATA,(size_t) myPic.header.bfOffBits,1,ok);
    fwrite(myPic.PIXELDATA,(size_t) myPic.header.bfSize - myPic.header.bfOffBits,1,ok);
    fclose(ok);
}


BMPPic_ applyFilter(BMPPic_ myPic){
    for (int i = 0; i < myPic.height; ++i) {
        for (int j = 0; j < myPic.width; ++j) {
            double a= sqrt(pow(getGray(myPic,i,j-1)-getGray(myPic,i,j+1),2)+pow(getGray(myPic,i-1,j)-getGray(myPic,i+1,j),2));
        }
    }
    return myPic;
}


int main_(FILE *file){
    BMPPic_ myPic;
    myPic = Init(file,myPic);

    //myPic = end(myPic);
    myPic = applyFilter(myPic);
    //myPic = end(myPic);


    restructPic(myPic);

    fclose(file);
}