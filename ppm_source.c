#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ppm_source.h"
//Some of the following code was brought up in tutorial
//This is a reference to it kinda?


void printPPM(Image *image){
    for (int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j ++)
            printf("#%02x%02x%02x ",image->data[i][j].r, image->data[i][j].g, image->data[i][j].b);
        printf("\n");
    }
}

Image *readPPM(char *file_name){
    FILE *file = fopen(file_name, "r");
    if (!file){
        fprintf(stderr, "unable to open file \"%s\"\n",file_name);
        return NULL;
    }
    
    char format[3];
    fscanf(file, "%s\n",format);
    if(strcmp(format, "P3")) return NULL;

    Image *image = malloc(sizeof(Image));

    if (fscanf(file, "%u %u %u", &image->width,&image->height,&image->max) != 3) return NULL;

    image->data = malloc(sizeof(Pixel *) * image->height);

    for (int i = 0; i < image->height; i ++)
        image->data[i] = malloc(sizeof(Pixel)*image->width); //stores pixels

    for (int i = 0; i < image->height; i++)
        for (int j = 0; j < image->width; j++){
            int pixels_read = fscanf(file, "%hhu %hhu %hhu",               
            &(image->data[i][j].r), &(image->data[i][j].g), &(image->data[i][j].b));
        if (pixels_read != 3)
            return NULL;
        }
    fclose(file);
    return (image);

};

int writePPM(char * file_name, Image *image){

    FILE *file = (fopen(file_name, "w"));
    if (!file){
        fprintf(stderr, "unalbe to open");
        return -1;
    }

    fprintf(file, "P3\n");
    fprintf(file, "%u %u\n", image->width, image->height);
    fprintf(file, "%u\n", image->max);

    for (int i = 0; i < image->height; i ++){
        for (int j = 0; j < image->width; j ++)
            fprintf(file, "%u %u %u ", image->data[i][j].r,image->data[i][j].g,image->data[i][j].b);
        fprintf(file,"\n");
    }
    fclose(file);
    return 0;
    
}
