#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "libPPM.h"
#include "conv.h"


int main(){

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

    PPM test1 = readPPM("res.ppm");
    PPMtoGreyScale(&test1);
    PPM test2 = convolute(test1, s);
    writePPM("resP.ppm", test2);


    return 0;
}