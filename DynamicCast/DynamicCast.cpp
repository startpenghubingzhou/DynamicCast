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
    future<fscore> score1;
    future<fscore> score2;
    chrono::milliseconds span(100);

    SAFEPOINTER(preins, new FreshFlower("/Users/penghubingzhou/Desktop/based.jpg", -0.46, 13.67, 18), return -1);

    basic_data = preins->get_data();

    SAFEPOINTER(nowins1, new DriedFlower("/Users/penghubingzhou/Desktop/test.jpg", basic_data), return -1);

    SAFEPOINTER(nowins2, new DriedFlower("/Users/penghubingzhou/Desktop/test2.jpg", basic_data), return -1);

    score1 = async(&DriedFlower::get_score, nowins1);
    score2 = async(&DriedFlower::get_score, nowins2);

    while (score1.wait_for(span) != future_status::ready || score2.wait_for(span) != future_status::ready) {
        continue;
    }

    fscore one = score1.get();
    fscore two = score2.get();

    printf("browning: %.3f, drytime: %.3f, fade: %.3f, transferred: %.3f, final: %.3f, grade: %d\n", one.browningscore, one.drytimescore, one.fadescore, one.transferredscore, one.finalscore, one.grade);

    printf("browning: %.3f, drytime: %.3f, fade: %.3f, transferred: %.3f, final: %.3f, grade: %d\n", two.browningscore, two.drytimescore, two.fadescore, two.transferredscore, two.finalscore, two.grade);

    return 0;
}

void releasesource() {
    SafeReleaseNULL(preins);
    SafeReleaseNULL(nowins1);
    SafeReleaseNULL(nowins2);
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
