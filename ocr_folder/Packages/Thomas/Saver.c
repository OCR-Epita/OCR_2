#include <stdio.h>
#include <stdlib.h>

#include "TraitementImage.h"
#include "Saver.h"


void save_(BMPPic_ myPic){
	unsigned char data[myPic.height*myPic.width];
	printf("%d\n", myPic.height);
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			data[(i*myPic.width) + j] = myPic.GREYMATRIX[i][j];
		}
	}
	printf("ok \n");
}