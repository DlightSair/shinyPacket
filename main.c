#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"
#include "libPPM.h"
#include "conv.h"

int sData[] = {
    -1, -1, -1,
    -1,  8, -1,
    -1, -1, -1
};

KERNEL s = {
    3,
    3,
    sData
};


int main(int argsc, char* argsv[])
{
    if(argsc < 4){
        printf("Incomplete Arguments!\n");
        return 1;
    }

    int IsGreyScale = 0, IsEdgeDetection = 0;
    
    char outputFile[64];
    char inputFile[64];

    strcpy(inputFile, argsv[1]);
    if(argsv[2][0] != '-') strcpy(outputFile, argsv[2]);

    for(int i=2; i < argsc; i++)
    {
        if(strcmp(argsv[i], "-h") == 0 || strcmp(argsv[i], "--help") == 0){
            printf("no help :(\n");
        }
        else if(strcmp(argsv[i], "-o") == 0){
            if(argsc < i+3){
                printf("Output File Not Provided!\n");
            }
            strcpy(outputFile, argsv[i+1]);
        }
        else if(strcmp(argsv[i], "-g") == 0 || strcmp(argsv[i], "--greyscale") == 0){
            IsGreyScale = 1;
        }
        else if(strcmp(argsv[i], "-ed") == 0 || strcmp(argsv[i], "--edgedetection") == 0){
            IsEdgeDetection = 1;
        }
    }

    if(!outputFile){
        printf("Output File Not Provided!\n");
        return 1;
    }
    

    PPM image = readPPM(inputFile);

    if(IsGreyScale){
        PPMtoGreyScale(&image);
    }

    if(IsEdgeDetection){
        image = convolute(image, s);
    }

    writePPM(outputFile, image);


    return 0;
}