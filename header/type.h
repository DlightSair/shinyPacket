#ifndef TYPE_H
#define TYPE_H

typedef struct{
    unsigned char r,g,b;
} pixel;


typedef struct{
    int width, height, maxColor;
    char format[3];
    pixel *image;
} PPM;


typedef struct{
    int width, height;
    int *seqMatrix;
} KERNEL;



#endif