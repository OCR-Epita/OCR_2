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

BMPPic_ getTextZones(BMPPic_ myPic);

#endif