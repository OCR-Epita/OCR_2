#include <string.h>
#include "../Thomas/TraitementImage.h"
#include <math.h>
#include "Binary.h"


histogram Get_window (histogram histo)
{
    /*int x = histo.scope.x;
    int y = histo.scope.y;
    histo.scope.nbr_greyscales = 0;

    histo.scope.greyscales = malloc(256);
    memset(histo.scope.greyscales,0,256);


    size_t i = x- (histo.scope.size/2);
    size_t j ;

    size_t borne_y = y + (histo.scope.size/2)+1;
    size_t borne_x = x+ (histo.scope.size/2 )+1;

    while(i<borne_x && i<histo.height && i >0) {
        j = y - (histo.scope.size / 2);
        while (j < borne_y && j < histo.height && j > 0) {
            int k = histo.GREYMATRIX[i][j];
            if (histo.scope.greyscales[k] == 0) {
                histo.scope.nbr_greyscales += 1;
            }
            histo.scope.greyscales[k] += 1;
            histo.nbr += 1;
            j += 1;
        }
        i += 1;
    }

    return histo;*/

    histo.scope.nbr_greyscales = 0;

    histo.scope.greyscales = malloc(256);
    memset(histo.scope.greyscales,0,256);


    size_t i = 0;
    size_t j ;

    size_t borne_y = histo.width;
    size_t borne_x = histo.height;

    while(i<borne_x ) {
        j = 0;
        while (j < borne_y ) {
            int k = histo.GREYMATRIX[i][j];
            if (histo.scope.greyscales[k] == 0)
            {
                histo.scope.nbr_greyscales += 1;
            }
            histo.scope.greyscales[k] += 1;
            histo.nbr += 1;
            j += 1;
        }
        i += 1;
    }

    return histo;

}


histogram Get_histo (BMPPic_ pic)
{
    int i = 0;
    int j = 0;

    histogram histo;
    histo.nbr = malloc(256);
    memset(histo.nbr,0,256);
    histo.GREYMATRIX = pic.GREYMATRIX;
    histo.height = pic.height;
    histo.width = pic.width;


    return histo;
}

int Sigma_mean (histogram histo)
{
    /*int x = histo.scope.x;
    int y = histo.scope.y;

    size_t i = x- (histo.scope.size/2);
    size_t j ;
    int res = 0;

    while(i<x+ (histo.scope.size/2)+1 && i<histo.height && i >0) {
        j = y - (histo.scope.size / 2);
        while (j < y + (histo.scope.size / 2) + 1 && j < histo.height && j > 0) {
            res += histo.GREYMATRIX[i][j];
            j += 1;
        }
        i += 1;
    }
    res /= (histo.scope.size * histo.scope.size);
    return res;*/
    //working
    int x = histo.scope.x;
    int y = histo.scope.y;

    size_t i = 0;
    size_t j ;
    int res = 0;

    while(i< histo.height) {
        j = 0;
        while (j < histo.width) {
            res += histo.GREYMATRIX[i][j];
            j += 1;
        }
        i += 1;
    }
    res /= (histo.height*histo.width);
    return res;
}

double Sigma_variance (histogram histo)
{
   /* int i = 0;
    double res = 0;


    while (i < 256)
    {
        double calcul = 0;
        if (histo.scope.greyscales[i] != 0) {
            calcul = ( pow(histo.GREYMATRIX[i][j],2) );
            calcul /= histo.scope.nbr_greyscales;
        }
        res += calcul;
        i+=1;
    }
    double l = res;
    res -= histo.mean ;
    return res;*/
    /*int x = histo.scope.x;
    int y = histo.scope.y;


    size_t i = x- (histo.scope.size/2);
    size_t j ;
    double calcul =0;
    int res = 0;

    while(i<x+ (histo.scope.size/2)+1 && i<histo.height && i >0) {
        j = y - (histo.scope.size / 2);
        while (j < y + (histo.scope.size / 2) + 1 && j < histo.height && j > 0) {


            calcul = ( histo.GREYMATRIX[i][j] - histo.mean )* ( histo.GREYMATRIX[i][j] - histo.mean );
            res += calcul;
            j += 1;
        }
        i += 1;
    }
    res /= (histo.scope.size * histo.scope.size);

    return res;*/
    int x = histo.scope.x;
    int y = histo.scope.y;


    size_t i = 0;
    size_t j ;
    double calcul =0;
    int res = 0;

    while(i< histo.height) {
        j = 0;
        while (j < histo.width) {


            calcul = ( histo.GREYMATRIX[i][j] - histo.mean )* ( histo.GREYMATRIX[i][j] - histo.mean );
            res += calcul;
            j += 1;
        }
        i += 1;
    }
    res /= (histo.width * histo.height);

    return res;
}


histogram Calculus (histogram histo,int x,int y)
{

    float ich =  Sigma_mean(histo);
    histo.mean = ich;
    histo.variance = Sigma_variance(histo)  ;
    return histo;

}


histogram Is_Bimodal (histogram histo)
{
    int Vt = 0;

    size_t var = histo.variance;

    if(histo.variance >= Vt)
        histo.Bimodal = 1;
    else
        histo.Bimodal=0;

    return histo;
}

double Get_Weight(histogram histo,int debut,int threshold)
{
    size_t size = histo.scope.size*histo.scope.size;
    int i = debut;
    int weight = 0;

    while (i < threshold)
    {

        weight += histo.scope.greyscales[i];
        i+=1;
    }
    weight /= size;
    return weight;
}

double Get_newMean (histogram histo,int debut ,int threshold)
{
    char* list = histo.scope.greyscales;

    int i = debut;
    int div = 1;
    double res = 0;

    while(i < threshold)
    {
        res += (i*histo.scope.greyscales[i]);
        div += histo.scope.greyscales[i];

        i+=1;
    }


    res /= div;
    return res;
}



double Get_newVariance (histogram histo,int debut,int threshold)
{

    char* list = histo.scope.greyscales;

    int i = debut;
    double res = 0;
    int div =0;
    double a = Get_newMean(histo,debut,threshold);

    while(i < threshold)
    {

        double val = (i - a )*(i-a)*histo.scope.greyscales[i];
        div += histo.scope.greyscales[i];
        res+=val;
        i+=1;
    }
    res /= div;
    return res;
}

int Bimodal_threshold (histogram histo)
{


    int threshold = 2;
    double value = 0;
    double res = 0;
    double mean = histo.mean;
    int dev = 0;


    while(threshold < 256)
    {
        double b =  Get_newMean(histo,threshold+1,256);
        double a = mean -b;
        res =  Get_Weight(histo,1,threshold) * Get_Weight(histo,threshold+1,256) * (( a -b)*(a-b));
        if(threshold == 2)
        {
            value = res;
        }
        if(res > value)
        {
            dev = threshold;
            value = res;
        }

        threshold +=1;
    }
    return dev;
    return 80;
}


BMPPic_ Changing (BMPPic_ pic,int threshold,size_t x,size_t y)
{
    /*Pixel_ pixel = getPixel(pic,x,y);*/
    if (pic.GREYMATRIX[x][y] > threshold)
    {

        pic = setGray(pic,x,y,255);
    }
    else
    {
        pic = setGray(pic,x,y,0);
    }
    return pic;

}

BMPPic_ end (BMPPic_ pic)
{
    int i = 0;
    int j ;
    histogram histo = Get_histo(pic);
    histo = Get_window(histo);
    histo = Calculus(histo,i,j);
    histo = Is_Bimodal(histo);
    histo.scope.x = i;
    histo.scope.y = j;
    histo.scope.size = 5;
    histo.Bimodal = 1;
    int threshold = Bimodal_threshold(histo);

    while (i < pic.height)
    {
        j=0;
        while (j < pic.width)
        {






            if ( histo.Bimodal == 1)
            {

                Changing(pic,threshold,i,j);
            }


            j+=1;
        }
        //printf("%d \n",i);
        i+=1;
    }
    //free(histo.nbr);
    //free(histo.scope.greyscales);
    return pic;
}
