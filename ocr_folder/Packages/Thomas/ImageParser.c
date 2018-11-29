#include <stdio.h>
#include <stdlib.h>
#include "TraitementImage.h"
#include "ImageParser.h"

void SaveMatrixToFile(unsigned char ** ARRAY, size_t height,size_t width){
	unsigned char * MATRIX = malloc(height * width * sizeof(unsigned char));
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			MATRIX[i*width + j] = ARRAY[i][j];
		}
	}
	FILE* file = fopen("DATABASE","w+");
	fwrite(MATRIX,1,height*width,file);
	fclose(file);
	free(MATRIX);
}

unsigned char ** InitMatrix(size_t height, size_t width, unsigned char value){
	unsigned char  ** ARRAY = malloc(height * width * sizeof(unsigned char));
	for (size_t i = 0; i < height; i++) {
		ARRAY[i] = malloc(width * sizeof(unsigned char));
		for (size_t j = 0; j < width; j++) {
			ARRAY[i][j] = value;
		}
	}
	return ARRAY;
}

BMPPic_ getTextZones(BMPPic_ myPic, BMPPic_ RLSAPic){

	unsigned char ***ZONES;
	ZONES = malloc(1);*
	size_t size_of_ZONES = 1;

	unsigned char ** alreadyTreat = InitMatrix(myPic.height,myPic.width,0);

	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			if(RLSAPic.GREYMATRIX[i][j] == 0 && alreadyTreat[i][j] == 0)
			{
				unsigned char **TAB = malloc(1);
				size_t tp_i = i;
				size_t TABLength = 1;
				size_t height = 0;
				size_t width = 0;
				while (RLSAPic.GREYMATRIX[tp_i][j] == 0)
				{
					size_t tp_j = j;
					unsigned char * LINE = malloc(1);
					while (RLSAPic.GREYMATRIX[tp_i][tp_j] == 0)
					{
						LINE = (unsigned char*) realloc(LINE,(tp_j-j+1));
						LINE[tp_j - j] = myPic.GREYMATRIX[tp_i][tp_j];
						alreadyTreat[tp_i][tp_j] = 1;
						if (width < tp_j - j) {
							width = tp_j - j;
						}
						++ tp_j;
					}
					TABLength += tp_j - j;
					TAB = (unsigned char **) realloc(TAB,TABLength);
					TAB[tp_i - i] = malloc(tp_j - j);
					TAB[tp_i - i] = LINE;
					if (height < tp_i - i) {
						height = tp_i - i;
					}
					++ tp_i;
				}
				SaveMatrixToFile(TAB,height,width);
			}
		}
	}
	//SaveMatrixToFile(myPic.GREYMATRIX,myPic.height,myPic.width);
	for (size_t i = 0; i < myPic.height; ++i)
	{
		free(alreadyTreat[i]);
	}
	free(alreadyTreat);

	return myPic;
}
