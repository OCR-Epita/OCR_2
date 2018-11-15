//
// Created by lucas on 06/11/18.
//

#include "Segmentation.h"
#include "../Thomas/TraitementImage.h"
#include <string.h>


void Color_colomn (BMPPic_ MyPic,size_t line)
{
    size_t i = 0;

    while(i < MyPic.height)
    {
        if(getGray(MyPic,i,line) == 255) {
            setGray(MyPic, i, line, 80);
        }
        i+=1;
    }

}
BMPPic_ Get_Space_Paragraph (BMPPic_ MyPic)
{
    size_t i = 0;
    size_t j;
    float res;
    size_t collons[MyPic.width];
    for (size_t l = 0; l < MyPic.width; ++l) {
        collons[l] = 0;
    }
    int k =0;


    while(i<MyPic.width)
    {
        j = 0;
        res = 0;
        while(j< MyPic.height)
        {
            if(getGray(MyPic,j,i) == 0)
            {
                res +=1;
            }
            j+=1;
        }
        if(res/MyPic.height < 0.1)
        {
            collons[k] = i;
            Color_colomn(MyPic,i);
            k+=1;
        }
        i+=1;
    }

    /*int print = 0;
    while(print < MyPic.width)
    {
        printf("%zu \n",collons[print]);
        print+=1;
    }*/

    MyPic.last = k-1;
    MyPic.colons_scope = collons;
    return MyPic;

}

void Color_line (BMPPic_ MyPic,size_t line)
{
    size_t i = MyPic.colons_scope[0];
    int last = MyPic.last;

    while(i < MyPic.colons_scope[last])
    {
       setGray(MyPic,line,i,80);
       i+=1;
    }

}

BMPPic_ Get_horizontal_Paragraph (BMPPic_ MyPic)
{
    size_t i = 0;
    size_t j;
    float res;
    size_t collons[MyPic.height];
    for (size_t l = 0; l < MyPic.height; ++l) {
        collons[l] = 0;
    }
    int k =0;


    while(i < MyPic.height)
    {
        j = 200;
        res = 0;
        while(j< MyPic.width)
        {
            if(getGray(MyPic,i,j) == 0)
            {
                res +=1;
            }
            j+=1;
        }
        if(res/MyPic.height < 0.1)
        {
            collons[k] = i;
            Color_line(MyPic,i);
            k+=1;
        }
        i+=1;
    }

    return MyPic;

}
