#include <stdio.h>
#include <stdlib.h>
#include "TraitementImage.h"
#include "ImageParser.h"


BMPPic_ getTextZones(BMPPic_ myPic){
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			printf("%zu %zu\n",i,j);
		}
	}

	return myPic;
}
