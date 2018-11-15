#include <stdio.h>
#include <stdlib.h>

#include "TraitementImage.h"
#include "Saver.h"


void save_(BMPPic_ myPic){
	unsigned char data[myPic.height*myPic.width];
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			data[(i*myPic.width) + j] = myPic.GREYMATRIX[i][j];
		}
		//free(myPic.GREYMATRIX[i]);
	}
	FILE* file = fopen("GREYMATRIX","w+");
	fwrite(data,myPic.height*myPic.width,sizeof(unsigned char),file);
	fclose(file);
}

BMPPic_ load_(BMPPic_ myPic){
	return myPic;
}