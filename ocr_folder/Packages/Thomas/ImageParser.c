#include <stdio.h>
#include <stdlib.h>
#include "TraitementImage.h"
#include "ImageParser.h"
#include "FreeMyPic.h"

void SaveMatrixToFile(unsigned char ** ARRAY, size_t height,size_t width){
	unsigned char * MATRIX = malloc(height * width * sizeof(unsigned char));
	for (size_t i = 0; i < height; i++) {
		for (size_t j = 0; j < width; j++) {
			MATRIX[i*width + j] = ARRAY[i][j];
		}
	}
	FILE* file = fopen("Matrix","w+");
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
	char alrdTrt[myPic.height][myPic.width];

	for (size_t i = 0; i < myPic.height; i++) {
		for (size_t j = 0; j < myPic.width; j++) {
			alrdTrt[i][j] = 0;
			size_t tp_i = i;
			size_t tp_j = j;
			while (RLSAPic.GREYMATRIX[tp_i][tp_j] == 0 && alrdTrt[tp_i][tp_j] == 0) {
				while (RLSAPic.GREYMATRIX[tp_i][tp_j] == 0 && alrdTrt[tp_i][tp_j] == 0) {
					alrdTrt[i][j] = 1;
					//printf("i = %d, j = %d \n", tp_i, tp_j);
					if(tp_j + 1 < myPic.width)
						++ tp_j;
					else
						break;
				}
				if(tp_i + 1 < myPic.height)
					++ tp_i;
				else
					break;
			}
		}
	}



	return myPic;
}
