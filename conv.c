#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "type.h"

void bound(int *val){
    if(*val > 255) *val = 255;
    if(*val < 0) *val = 0;
}

PPM convolute(PPM imagePPM, const KERNEL kernel){

    PPM imageOUT = {
        .width = imagePPM.width,
        .height = imagePPM.height,
        .maxColor = imagePPM.maxColor,
        .image = calloc( imageOUT.width * imageOUT.height , sizeof(pixel))
    };

    strcpy(imageOUT.format, imagePPM.format);

    for(int i=0; i<imageOUT.height; i++){
        for(int j=0; j<imageOUT.width; j++){

            int seq1 = j + i * imageOUT.width;
            int sumR=0, sumG = 0, sumB = 0;

            for(int k=0; k< kernel.height; k++){
                for(int l=0; l< kernel.width; l++){

                    int kerSeq = l + k * kernel.width;
                    int x = j + l - kernel.width/2;
                    int y = i + k - kernel.height/2;
                    int seq2 = x + y * imageOUT.width;
                    
                    if( (x >=0 && x < imageOUT.width) && (y >=0 && y < imageOUT.height)){
                        sumR += kernel.seqMatrix[kerSeq] * (imagePPM.image+seq2)->r;
                        sumG += kernel.seqMatrix[kerSeq] * (imagePPM.image+seq2)->g;
                        sumB += kernel.seqMatrix[kerSeq] * (imagePPM.image+seq2)->b;
                    }

                }
            }

            bound(&sumR); bound(&sumG); bound(&sumB);

            (imageOUT.image+seq1)->r = sumR;
            (imageOUT.image+seq1)->g = sumG;
            (imageOUT.image+seq1)->b = sumB;

        }
    }

    return imageOUT;

}