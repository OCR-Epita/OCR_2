#include <stdio.h>
#include <stdlib.h>
#include "TraitementImage.h"
#include "ImageParser.h"


size_t Line(unsigned char* line,size_t i,size_t j,BMPPic_ RLSAPic,BMPPic_ myPic){
	int index = 0;
	while(myPic.GREYMATRIX[i][j] == 0){
		printf("j = %d \n", j);
		line = realloc(line,index + 1);
		line[index] = myPic.GREYMATRIX[i][j];
		j += 1;
	}
	return j;
}

unsigned char ** InitMatrix(unsigned char** matrix,size_t height,size_t width,unsigned char value){
	matrix = malloc(height * width * sizeof(unsigned char));
	for (size_t i = 0; i < height; i++) {
		matrix[i] = malloc(width * sizeof(unsigned char));
		for (size_t j = 0; j < width; j++) {
			matrix[i][j] = value;
		}
	}
	return matrix;
}

BMPPic_ getTextZones(BMPPic_ myPic, BMPPic_ RLSAPic){
	unsigned char **alreadyTreat;
	alreadyTreat = InitMatrix(**alreadyTreat,myPic.height,myPic.width,0);
	printf("%d \n", alreadyTreat[0][0]);
	for (size_t i = 0; i < myPic.height; ++i)
	{
		for (size_t j = 0; j < myPic.width; ++j)
		{
			if(RLSAPic.GREYMATRIX[i][j] == 0 && alreadyTreat[i][j] == 0)
			{
				alreadyTreat[i][j] = 1;
			}
		}
	}

	for (size_t i = 0; i < myPic.height; ++i)
	{
		free(alreadyTreat[i]);
	}
	free(alreadyTreat);

	return myPic;
}
