#include "../Thomas/TraitementImage.h"
#include <stdio.h>
#include <stdlib.h>

BMPPic_ Get_lines (BMPPic_ MyPic)
{

    ligne MyLine;
    MyLine.lenght = 2;
    MyLine.upper_left_x = 0;
    MyLine.upper_left_y = 0;
    MyLine.bottom_right_y = 0;
    MyLine.bottom_right_x = 0;


    size_t i = 1;
    size_t j;
    ligne* lines = 0;
    int pending = 0;
    int k = 0;
    lines = calloc(0,1000);

    while(i < MyPic.height)
    {
        j = 1;
        while (j < MyPic.width)
        {
            if(getGray(MyPic,i,j) == 0 && getGray(MyPic,i-1,j) == 80 && getGray(MyPic,i,j-1) == 80 && pending == 0)
            {

                MyLine.upper_left_x = i;
                MyLine.upper_left_y = j;
                pending = 1;
            }
            if(getGray(MyPic,i,j) == 255 && getGray(MyPic,i-1,j) == 80 && getGray(MyPic,i,j-1) == 80 && pending == 0)
            {

                MyLine.upper_left_x = i;
                MyLine.upper_left_y = j;
                pending = 1;
            }
            if(getGray(MyPic,i,j) == 0 && getGray(MyPic,i+1,j) == 80 && getGray(MyPic,i,j+1) == 80 && pending ==1)
            {
                MyLine.bottom_right_x = i;
                MyLine.bottom_right_y = j;
                lines[k] = MyLine;
                k+=1;
                pending = 0;
            }
            if(getGray(MyPic,i,j) == 255 && getGray(MyPic,i+1,j) == 80 && getGray(MyPic,i,j+1) == 80 && pending == 1)
            {
                MyLine.bottom_right_x = i;
                MyLine.bottom_right_y = j;
                lines[k] = MyLine;
                k+=1;
                pending =0;
            }
            j+=1;
        }
        i +=1;
    }
    return MyPic;
}