#include <stdio.h>
#include <stdlib.h>

#include "TraitementImage.h"



BMPPic_ getTextZones(BMPPic_ myPic){
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			if (myPic.GREYMATRIX[i][j] == 0)
			{
				myPic.GREYMATRIX[i][j] = 124;
			}
		}
	}
	

	return myPic;
}