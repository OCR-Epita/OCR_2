#include "FreeMyPic.h"

void FreeAll(BMPPic_ myPic){
  free(myPic.PIXELDATA);
  free(myPic.HEADERDATA);
  free(myPic.PIXELDATA);
  for (size_t i = 0; i < myPic.height; ++i)
  {
    free(myPic.GREYMATRIX[i]);
  }
  free(myPic.GREYMATRIX);
}


void FreePIXELDATA(BMPPic_ myPic){
  free(myPic.PIXELDATA);
}

void FreeGREYMATRIX(BMPPic_ myPic){
  for (size_t i = 0; i < myPic.height; i++) {
    free(myPic.GREYMATRIX[i]);
  }
  free(myPic.GREYMATRIX);
}
