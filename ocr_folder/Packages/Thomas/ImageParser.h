#ifndef PROJECT2_IMAGEPASER_H
#define PROJECT2_IMAGEPASER_H

typedef struct
{
	size_t x;
	size_t y;
} POINT_;


typedef struct
{
	POINT_ a;
	POINT_ b;
	POINT_ c;
	POINT_ d;
} TEXTZONE_;

void SaveMatrixToFile(unsigned char ** ARRAY, size_t height,size_t width);

unsigned char ** InitMatrix(size_t height, size_t width, unsigned char value);

BMPPic_ getTextZones(BMPPic_ myPic,BMPPic_ RLSAPic);

#endif
