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

unsigned char ** InitMatrix(unsigned char** matrix,size_t height,size_t width,unsigned char value);

size_t Line(unsigned char* line,size_t i,size_t j,BMPPic_ RLSAPic,BMPPic_ myPic);

BMPPic_ getTextZones(BMPPic_ myPic,BMPPic_ RLSAPic);

#endif
