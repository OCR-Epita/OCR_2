#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include "Packages/lucas/Binary.h"

#include "Packages/Thomas/TraitementImage.h"

int main(){
    FILE *file = fopen("../Images/Amaury.bmp","a+");
    main_(file);
    return 0;
}