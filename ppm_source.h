#ifndef PPM_SOURCE_H
#define PPM_SOURCE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pixel {
     unsigned char r, b, g;
} Pixel;

typedef struct image {
    unsigned int width, height, max;
    Pixel ** data;
} Image;

void printPPM(Image *image);
Image *readPPM(char *file_name);
int writePPM(char * file_name, Image *image);

#endif
