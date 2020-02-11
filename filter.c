//William Lee
//400174625
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Some of the following code was brought up in tutorial
//This is a reference to it kinda?

typedef struct pixel {
     unsigned char r, b, g;
} Pixel;

typedef struct image {
    unsigned int width, height, max;
    Pixel ** data;
} Image;


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


//spot in kernel
#define K_SPOT(i,k,n) (   ((k)+(n/2)) * (n)  + (i) + (n/2)   )

Image * ApplyFilter(Image *image_in, int n,int divider, int kernel[n]){

   Image *image_out = image_in;
    
    
    int accum_r = 0;
    int accum_g = 0;
    int accum_b = 0;


    for (int h = 0; h < image_in->height; h ++){
        for (int w = 0; w < image_in->width; w++){// cycles through every pixel
            accum_r = 0;
            accum_g = 0;
            accum_b = 0;
            
            for (int k = -(n/2); k < n -(n/2); k ++){ //kernel row
               for (int i = -(n/2); i < n -(n/2); i ++){ //each element in row


                if (!(h + k >= image_in->height || w + i >= image_in->width || h + k <= 0 || w + i <= 0)){
                accum_r   +=   (kernel[K_SPOT(i,k,n)]    *    (image_in->data[h+k][w+i].r));
                accum_g   +=   (kernel[K_SPOT(i,k,n)]    *    (image_in->data[h+k][w+i].g));
                accum_b   +=   (kernel[K_SPOT(i,k,n)]    *    (image_in->data[h+k][w+i].b));

                }
               }
            } 

            image_out->data[h][w].r = accum_r/divider;
            image_out->data[h][w].g = accum_g/divider;
            image_out->data[h][w].b = accum_b/divider;

        }
    }
    return image_out;
}


int main(int argc, char** argv){

    if ( argc != 4){
         printf("Incorrect input \n");
         return -1;
     }

    Image *image = readPPM(argv[1]);
    if (!image)
         return -1;

    FILE* in_file;
    in_file = fopen(argv[2], "r");
    int n, divider;
    
    fscanf(in_file, "%d \n %d \n", &n, &divider);
    int kernel[n*n];
    int counter = 0;
    while (!feof(in_file)){
        fscanf(in_file,"\n%d ", &kernel[counter]);
        counter ++;
    }
    
    char * outfile = argv[3];
    writePPM(outfile, ApplyFilter(image,n,divider,kernel) );
    
    return 0;
}

