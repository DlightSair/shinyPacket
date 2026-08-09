#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "type.h"
#include <ctype.h>

void skipCommentsandSpace(FILE *fptr)
{
    int c;

    while (1)
    {
        while ((c = fgetc(fptr)) != EOF && isspace(c))
            ;

        if (c == '#')
        {
            while ((c = fgetc(fptr)) != EOF && c != '\n')
                ;
        }
        else
        {
            if (c != EOF) ungetc(c, fptr);

            break;
        }
    }
}

PPM readPPM(char *const filename)
{
    PPM imagePPM;
    FILE *fptr = fopen(filename, "rb");
    if(!fptr) {printf("File \"%s\" Failed to open\n", filename); return (PPM){0,0};};

    skipCommentsandSpace(fptr);
    fscanf(fptr, "%2s", imagePPM.format);

    skipCommentsandSpace(fptr);
    fscanf(fptr, "%d %d", &imagePPM.width, &imagePPM.height);
    skipCommentsandSpace(fptr);
    fscanf(fptr, "%d", &imagePPM.maxColor);
    skipCommentsandSpace(fptr);

    int pixelArea = imagePPM.height * imagePPM.width;

    imagePPM.image = malloc( pixelArea * sizeof(pixel));

    if(strcmp(imagePPM.format, "P6") == 0){
        fread(imagePPM.image, sizeof(pixel), pixelArea, fptr);

    } else if(strcmp(imagePPM.format, "P3") == 0) {
        for(int i=0; i<pixelArea; i++){

            fscanf(fptr, "%hhu %hhu %hhu",
                &(imagePPM.image+i)->r,
                &(imagePPM.image+i)->g,
                &(imagePPM.image+i)->b);
                 
        }
    }

    strncpy(imagePPM.format, "P3", 3);

    fclose(fptr);
    return imagePPM;
}



PPM createPPM(int width, int height, float weight, char *format)
{
    if(width < 0 || height < 0) return (PPM){0};
    if(weight < 0) weight = 0;
    if(weight > 1) weight = 1;
    
    PPM imagePPM;
    int pixelArea = width*height;

    imagePPM.width = width;
    imagePPM.height = height;
    imagePPM.maxColor = 255;
    strncpy(imagePPM.format, format, 3);

    imagePPM.image = malloc( pixelArea * sizeof(pixel));
    int val = (int) imagePPM.maxColor * weight;

    for(int i=0; i<pixelArea; i++){
        (imagePPM.image+i)->r = val;
        (imagePPM.image+i)->g = val;
        (imagePPM.image+i)->b = val;
    }

    return imagePPM;
}


void writePPM(char *const filename, PPM imagePPM)
{
    FILE *fptr = fopen(filename, "w");
    if(!fptr) return;

    fprintf(fptr, "%s\n", imagePPM.format);
    fprintf(fptr, "%d %d\n", imagePPM.width, imagePPM.height);
    fprintf(fptr, "%d\n", imagePPM.maxColor);

    for(int i=0; i<imagePPM.height; i++){
        for(int j=0; j<imagePPM.width; j++){

            int k = j+imagePPM.width*i;
            fprintf(fptr, "%hhu %hhu %hhu ", 
                (imagePPM.image+k)->r, 
                (imagePPM.image+k)->g, 
                (imagePPM.image+k)->b);
        }
        fprintf(fptr, "\n");
    }
    fclose(fptr);
}


void PPMtoGreyScale(PPM *imagePPM)
{
    if(strcmp(imagePPM->format, "P3")){printf("Only P3 supported\n"); return;}
    for(int i=0; i<imagePPM->height; i++){
        for(int j=0; j<imagePPM->width; j++){
            int k = j+(imagePPM->width)*i;

            int val = (int) ( 0.299 * (imagePPM->image+k)->r
                + 0.587 * (imagePPM->image+k)->g 
                + 0.114 * (imagePPM->image+k)->g );

            (imagePPM->image+k)->r = val;
            (imagePPM->image+k)->g = val;
            (imagePPM->image+k)->b = val;   
        }
    }
}