#include <stdio.h>
#include <stdlib.h>

#include "TraitementImage.h"
#include "Saver.h"


void save_(BMPPic_ myPic){
	unsigned char DATA[myPic.height][myPic.width];
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			DATA[i][j] = myPic.GREYMATRIX[i][j];
		}
	}
	printf("ok \n");
}