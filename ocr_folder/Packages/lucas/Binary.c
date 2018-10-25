#include <string.h>
#include "../Thomas/TraitementImage.h"
#include <math.h>
#include "Binary.h"



//Get the histogramm of a image
histogram Get_window (histogram histo)
{

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

//Define the histogram
histogram Get_histo (BMPPic_ pic)
{
    histogram histo;
    histo.nbr = malloc(256);
    memset(histo.nbr,0,256);
    histo.GREYMATRIX = pic.GREYMATRIX;
    histo.height = pic.height;
    histo.width = pic.width;


    return histo;
}

//Get the mean of the histogram
int Sigma_mean (histogram histo)
{

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

//Get the variance of the histogram
double Sigma_variance (histogram histo)
{

    size_t i = 0;
    size_t j ;
    double calcul =0;
    double res = 0;

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



//put the results in the histogram parameters
histogram Calculus (histogram histo)
{

    float ich =  Sigma_mean(histo);
    histo.mean = ich;
    histo.variance = Sigma_variance(histo)  ;
    return histo;

}


// tell us if the image is binomial
histogram Is_Bimodal (histogram histo)
{
    int Vt = 0;


    if(histo.variance >= Vt)
        histo.Bimodal = 1;
    else
        histo.Bimodal=0;

    return histo;
}

//Determine the weight of a pixel
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

//used in a previous version to get the new mean if the size of the window is increaseed
double Get_newMean (histogram histo,int debut ,int threshold)
{

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



/*double Get_newVariance (histogram histo,int debut,int threshold)
{

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
}*/

//Use to get the threshold
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
}


//Change pixel in fonction of the threshold value
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

//aplly the binarisation
BMPPic_ end (BMPPic_ pic)
{
    int i = 0;
    int j = 0;
    histogram histo = Get_histo(pic);
    histo = Get_window(histo);
    histo = Calculus(histo);
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

                Changing(pic, threshold, (size_t) i, (size_t) j);
            }


            j+=1;
        }
        i+=1;
    }

    return pic;
}
