#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Packages/lucas/Binary.h"
#include "Packages/Thomas/TraitementImage.h"
#include "Packages/Thomas/ImageParser.h"
int main()
{
	FILE *file = fopen("Images/black_square.bmp","a+");
    treatPic(file);
	return 0;
}