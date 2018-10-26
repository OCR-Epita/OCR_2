
#ifndef PROJECT2_BINARY_H
#define PROJECT2_BINARY_H
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "../Thomas/Process.h"

typedef struct {


    size_t size;
    size_t nbr_greyscales;
    unsigned char * greyscales;

    double weight;
    double mean_pixel;


    int x;
    int y;


} window;


typedef struct {


    window scope;

    double mean;
    double variance;

    int *nbr;
    unsigned char **GREYMATRIX;
    size_t height;
    size_t width;

    int Bimodal;
} histogram;

BMPPic_ end (BMPPic_ pic);




#endif //PROJECT2_BINARY_H
