#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ppm_source.h"

Image * ApplyFilter(Image *image_in, int n,int divider, signed int kernel[n]);

int main(int argc, char** argv){

    /* if ( argc != 3){
    //     printf("Incorrect  input \n");
    //     return -1;
    // }*/

    Image *image = readPPM(argv[1]);
    /* if (!image)
    //     return -1;*/

    FILE* in_file;
    in_file = fopen(argv[2], "r");
    /*writePPM("out.ppm", image);*/

    int n, divider;
    int kernel[9];
    fscanf(in_file, "%d \n %d \n", &n, &divider);
    /* while (!feof(in_file)){

    // }*/

    printf("n = %d d = %d\n",n,divider);
    /*writePPM(argv[3], ApplyFilter(image,n,divider,kernel)  );*/
}
