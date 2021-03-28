//
//  DynamicCast.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/2/13.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include <iostream>

#include "DynamicCast.hpp"

int main(int argc, char **argv) {
    string pre, now;

    detectargs(argc, argv);

    SAFEPOINTER(based, new CVHelper(argv[1]), {
        goto main_error;
    });

    SAFEPOINTER(test, new CVHelper(argv[2]), {
        goto main_error;
    });

    pre = based->prasecolor_pixel();
    now = test->prasecolor_pixel();

    if (pre == now) {
        funcprint("color has not changed!\n");
    } else {
        funcprint("color has changed from %s to %s!\n", pre.c_str(), now.c_str());
    }

    releasesource();

    return 0;

main_error:
    releasesource();

    return -1;
}

void releasesource() {
    SafeReleaseNULL(based);
    SafeReleaseNULL(test);
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
