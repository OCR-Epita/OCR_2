#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Packages/lucas/Binary.h"
#include "Packages/Thomas/Process.h"

int main()
{
	FILE *file = fopen("Images/QCM.bmp","a+");
    main_(file);
	return 0;
}