#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lucas/Binary.h"
#include "../lucas/Segmentation.h"
#include "TraitementImage.h"
#include "ImageParser.h"

//Get the header of the bmp image thanks to it's hexadecimal representation
BMPPic_ getHeader(char data[]){
    BMPPic_ myPic;
    myPic.header.bftype = *((short *) (data + 0));
    myPic.header.bfSize = *((int *) (data + 2));
    myPic.header.bfReserved1 = *((short *) (data + 6));
    myPic.header.bfReserved2 = *((short *) (data + 8));
    myPic.header.bfOffBits = *((data + 10));
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


//Initialize an image
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

//Get the greyscale image out of the original one
BMPPic_ InitGreyMatr(BMPPic_ myPic){
    myPic.GREYMATRIX = malloc(myPic.height*myPic.width*sizeof(char));
    for (size_t i = 0; i < myPic.height; ++i) {
        myPic.GREYMATRIX[i]=malloc(myPic.width* sizeof(char));
        for (size_t j = 0; j < myPic.width; ++j) {
            Pixel_ tp = getPixel(myPic,i,j);
            unsigned char a = (unsigned char) ((tp.B + tp.V + tp.R) / 3);
            myPic.GREYMATRIX[i][j]=a;
        }
    }
    return myPic;
}

//Allow us to get a pixel values thanks to it's position
Pixel_ getPixel(BMPPic_ myPic,size_t i,size_t j){
    Pixel_ cur;
    cur.R = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 0];
    cur.V = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 1];
    cur.B = myPic.PIXELDATA[i*myPic.width*3 + j*3 + 2];
    return cur;
}

//Allow us to change a pixel thanks to it's position
BMPPic_ setPixel(BMPPic_ myPic,size_t i,size_t j,Pixel_ pixel){
    if(i >= myPic.height || j >= myPic.width)
        err(1,"ERREUR: setpixel arg i et j");
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 0] = pixel.R;
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 1] = pixel.V;
    myPic.PIXELDATA[i*myPic.width*3 + j*3 + 2] = pixel.B;
    return myPic;
}

//Same thing for GetPixel but for greyscale image
unsigned char getGray(BMPPic_ myPic,size_t x, size_t y){
    unsigned char res = 0;
    if(x < myPic.height && y < myPic.width)
        res = myPic.GREYMATRIX[x][y];
    return res;
}

//Same thing for SetPixel but for greyscale image
BMPPic_ setGray(BMPPic_ myPic,size_t x, size_t y,unsigned char val){
    myPic.GREYMATRIX[x][y] = val;
    return myPic;
}

//Recontrsuct the image, helpfull to check the accuracy of our fonctions
void restructPic(BMPPic_ myPic, char name[]){
    
    for (size_t i = 0; i < myPic.height; ++i) {
        for (size_t j = 0; j < myPic.width; ++j) {
            Pixel_ cur;
            cur.R = myPic.GREYMATRIX[i][j];
            cur.V = myPic.GREYMATRIX[i][j];
            cur.B = myPic.GREYMATRIX[i][j];
            myPic = setPixel(myPic,i,j,cur);
        }
    }
    FILE *ok;
    ok = fopen(name,"w+");
    fwrite(myPic.HEADERDATA,(size_t) myPic.header.bfOffBits,1,ok);
    fwrite(myPic.PIXELDATA,(size_t) myPic.header.bfSize - myPic.header.bfOffBits,1,ok);
    fclose(ok);
    
}

//Get the edges of shapes used to binarize an image with text
BMPPic_ applyFilter(BMPPic_ myPic){
    
    long **DATA = calloc(myPic.height*myPic.width, sizeof(long));
    long max = 0;
    long min = 999999;
    for (size_t i = 0; i < myPic.height; ++i) {
        DATA[i] = calloc(myPic.width, sizeof(long));
        for (size_t j = 0; j < myPic.width; ++j) {
            DATA[i][j] = (long) sqrt(pow(getGray(myPic, i, j - 1) - getGray(myPic, i, j + 1), 2) + pow(getGray(myPic, i - 1, j) - getGray(myPic, i + 1, j), 2));
            if(DATA[i][j] > max)
                max = DATA[i][j];
            if(DATA[i][j] < min)
                min = DATA[i][j];
        }
    }
    float seuil = (float) (min + (0.2 * (max - min)));
    for (size_t k = 0; k < myPic.height; ++k) {
        for (size_t i = 0; i < myPic.width; ++i) {
            if(DATA[k][i] > seuil)
                setGray(myPic,k,i,0);
            else
                setGray(myPic,k,i,255);
        }
        free(DATA[k]);
    }
    free(DATA);
    
    return myPic;
}

//Detect text on an image
BMPPic_ ApplyRLSA(BMPPic_ myPic,int seuil_a,int seuil_b){
    
    double seuil = seuil_a;
    char data_x[myPic.height][myPic.width];
    char data_y[myPic.height][myPic.width];

    for (size_t i = 0; i < myPic.height; ++i) {
        memset(data_x[i],255, sizeof(data_x[i]));
        memset(data_y[i],255, sizeof(data_y[i]));
        int compt = 0;
        for (size_t j = 0; j < myPic.width ; ++j) {
            if(getGray(myPic,i,j) == 255)
                compt += 1;
            if(getGray(myPic,i,j) == 0){
                data_x[i][j] = 0;
                if(compt <= seuil){
                    for (int k = compt; k > 0; --k) {
                        //RLSAPICx = setGray(RLSAPICx,i,j-k,255);
                        data_x[i][j-k] = 0;
                    }
                }
                compt = 0;
            }
        }
    }

    seuil = seuil_b;



    for (size_t j = 0; j < myPic.width ; ++j) {
        int compt = 0;
        for (size_t i = 0; i < myPic.height; ++i) {
            if(getGray(myPic,i,j) == 255) {
                compt += 1;
            }
            if(getGray(myPic,i,j) == 0){
                data_y[i][j]=0;
                if(compt <= seuil){
                    for (int k = compt; k > 0; --k) {
                        data_y[i-k][j] = 0;
                    }
                }
                compt = 0;
            }
        }
    }

    for (size_t l = 0; l < myPic.height; ++l) {
        for (size_t i = 0; i < myPic.width; ++i) {
            int a = data_x[l][i];
            int b = data_y[l][i];
            int res = 255;
            if(a == 0 && b == 0)
                res = 0;

            myPic = setGray(myPic, (size_t) l, (size_t) i, (unsigned char) res);
        }
    }    
    return myPic;
} 

void FreePic(BMPPic_ myPic){
    free(myPic.HEADERDATA);
    free(myPic.PIXELDATA);
    for (size_t i = 0; i < myPic.height; ++i)
    {
        free(myPic.GREYMATRIX[i]);
    }
    free(myPic.GREYMATRIX);
}

BMPPic_ treatPic(FILE *file){

    BMPPic_ myPic;
    BMPPic_ rlsapic;
    myPic = Init(file,myPic);
    myPic = end(myPic);
    rlsapic = myPic;
    //myPic = applyFilter(myPic);
    myPic = ApplyRLSA(myPic,300,400);
    //myPic = applyFilter(myPic);
    myPic = getTextZones(myPic,rlsapic);
    restructPic(rlsapic,"result/res.bmp");
    FreePic(myPic);
    fclose(file);
    return myPic;
}