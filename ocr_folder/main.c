#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Packages/lucas/Binary.h"
#include "Packages/Thomas/TraitementImage.h"

int main()
{
	FILE *file = fopen("Images/lol.bmp","a+");
    main_(file);
	return 0;



	// RLSAPic = applyFilter(RLSAPic);

    // RLSAPic = ApplyRLSA(RLSAPic);

    // RLSAPic = Get_Space_Paragraph(RLSAPic);

    // RLSAPic = Get_horizontal_Paragraph(RLSAPic);

    // restructPic(RLSAPic,"result/result.bmp");
}