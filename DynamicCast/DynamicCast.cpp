//
//  DynamicCast.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/4/27.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "DynamicCast.h"

void myfunc() {
    printf("test!\n");
}

int main(int argc, char **argv) {
    return cast(argc, argv);
}

int cast(int argc, char **argv) {
    basedata.h_average = 1;
    
    SAFEPOINTER(preins, new FreshFlower("/Users/penghubingzhou/Desktop/based.jpg", -0.3, 0.1), return -1);

    SAFEPOINTER(nowins, new FreshFlower("/Users/penghubingzhou/Desktop/test.jpg", -0.3, 0.1), return -1);

    // use this while loop to implement a mechanism like spin-lock.
    while (!preins->haswritten_havg || !nowins->haswritten_havg) {
        continue;
    }

    printf("%.3f, %.3f\n", preins->data.h_average, nowins->data.h_average);
    
    return 0;
}

void releasesource() {
    SafeReleaseNULL(preins);
    SafeReleaseNULL(nowins);
}

void detectargs(int argc, char **argv) {
    if (argc == 2 && !strncmp(argv[1], "-h", 2)) {
        printf("usage: DynamicCast -origin -src\n");
        printf("-origin the origin flower image path\n");
        printf("-src the source flower image path\n");
        exit(0);
    }

    if ( argc != 3 ) {
        funcprint("wrong args! Type \"DynamicCast -h\" for help!\n");
        exit(0);
    }
}
