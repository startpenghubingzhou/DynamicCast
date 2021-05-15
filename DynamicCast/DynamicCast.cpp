//
//  DynamicCast.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/4/27.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "DynamicCast.h"
#include <future>

void myfunc() {
    printf("test!\n");
}

int main(int argc, char **argv) {
    return cast(argc, argv);
}

int cast(int argc, char **argv) {
    future<fdata> data1;
    future<fdata> data2;
    chrono::milliseconds span(100);

    SAFEPOINTER(preins, new FreshFlower("/Users/penghubingzhou/Desktop/based.jpg", -0.3, 0.1), return -1);

    SAFEPOINTER(nowins, new FreshFlower("/Users/penghubingzhou/Desktop/test.jpg", -0.3, 0.1), return -1);

    data1 = async(&FreshFlower::get_data, preins);
    data2 = async(&FreshFlower::get_data, nowins);

    while (data1.wait_for(span) != future_status::ready || data2.wait_for(span) != future_status::ready) {
        continue;
    }

    fdata one = data1.get();
    fdata two = data2.get();

    printf("%.3f, %.3f\n", one.h_average, two.h_average);

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
