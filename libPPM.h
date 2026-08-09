#ifndef LIBPPM_H
#define LIBPPM_H
#include "type.h"

PPM readPPM(char *const filename);
PPM createPPM(int width, int height, float greyScale, char *format);
void writePPM(char *const filename, PPM imagePPM);
void PPMtoGreyScale(PPM *imagePPM);

#endif