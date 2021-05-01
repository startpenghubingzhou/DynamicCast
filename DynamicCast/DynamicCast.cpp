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
    double pre, now, transratio;

    future<double> pre_fte, now_fte;
    promise<double> pre_pme, now_pme;

    detectargs(argc, argv);

    /* Allocate two CVHelper objects to process the pictures of the flower
     before and now */
    SAFEPOINTER(pre_pic, new CVHelper(argv[1]), {
        goto main_error;
    });

    SAFEPOINTER(now_pic, new CVHelper(argv[2]), {
        goto main_error;
    });

    // put the return string into future objects
    pre_fte = pre_pme.get_future();
    now_fte = now_pme.get_future();

    SAFEPOINTER(pre_t, new thread(&CVHelper::prasecolor_pixel, pre_pic, &pre_pme),
    {
        goto main_error;
    })

    SAFEPOINTER(now_t, new thread(&CVHelper::prasecolor_pixel, now_pic, &now_pme),
    {
        goto main_error;
    })

    pre_t->detach();
    now_t->detach();

    pre = pre_fte.get();
    now = now_fte.get();

    transratio = CAL_TRANSRATIO(pre, now);

    printf("the trans ratio is: %.1f%%\n", transratio * 100);

    releasesource();

    return transratio * 100;

main_error:
    releasesource();

    return -1;
}

void releasesource() {
    SafeReleaseNULL(pre_pic);
    SafeReleaseNULL(now_pic);
    SafeReleaseNULL(pre_t);
    SafeReleaseNULL(now_t);
}

void detectargs(int argc, char **argv) {
    if (argc == 2 && !strncmp(argv[1], "-h", 2)) {
        printf("usage: DynamicCast -origin -src\n");
        printf("-origin the origin flower image path\n");
        printf("-src the source flower image path\n");
        exit(0);
    }

    if ( argc != 3 ) {
        printf("%s::wrong args! Type \"DynamicCast -h\" for help!\n", "DynamicCast");
        exit(0);
    }
}
