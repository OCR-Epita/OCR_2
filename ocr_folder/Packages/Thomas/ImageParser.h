#ifndef PROJECT2_IMAGEPASER_H
#define PROJECT2_IMAGEPASER_H

struct zone{
	unsigned char** data;
	size_t height;
	size_t width;
};

struct imageZone{
	struct zone** zones;
	size_t size;
};

void SaveMatrixToFile(unsigned char ** ARRAY, size_t height,size_t width);

unsigned char ** InitMatrix(size_t height, size_t width, unsigned char value);

BMPPic_ getTextZones(BMPPic_ myPic,BMPPic_ RLSAPic);

#endif
