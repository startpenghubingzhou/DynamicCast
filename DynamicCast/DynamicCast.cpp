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
    future<sqlfscore*> score1;
    future<sqlfscore*> score2;
    chrono::milliseconds span(100);
    fdata* dataptr;

    if (DynamicCast_init("/Users/penghubingzhou/Desktop/Database.db")) {
        return -1;
    }

    dataptr = getbasedata("/Users/penghubingzhou/Desktop/based.jpg", -0.46, 13.67, 18);

    basic_data = *dataptr;

    score1 = async(getscoredata, "/Users/penghubingzhou/Desktop/test.jpg", &basic_data, 6);
    score2 = async(getscoredata, "/Users/penghubingzhou/Desktop/test2.jpg", &basic_data, 7);

    while (score1.wait_for(span) != future_status::ready || score2.wait_for(span) != future_status::ready) {
        continue;
    }

    sqlfscore* one = score1.get();
    sqlfscore* two = score2.get();

    printf("browning: %.3f, drytime: %.3f, fade: %.3f, transferred: %.3f, final: %.3f, grade: %d\n", one->score.browningscore, one->score.drytimescore, one->score.fadescore, one->score.transferredscore, one->score.finalscore, one->score.grade);

    printf("browning: %.3f, drytime: %.3f, fade: %.3f, transferred: %.3f, final: %.3f, grade: %d\n", two->score.browningscore, two->score.drytimescore, two->score.fadescore, two->score.transferredscore, two->score.finalscore, two->score.grade);

    writedata(one);
    writedata(two);

    release_score_data(one);
    release_score_data(two);

    SafeReleaseNULL(sqlins);

    return 0;
}

int DynamicCast_init(const char* dbpath) {
    SAFEPOINTER(sqlins, new SQLFriend(dbpath), return -1);
    return 0;
}

fdata* getbasedata(const char* name, double k, double b, double t) {
    fdata* data;
    FreshFlower* instance;

    if (!name) {
        return nullptr;
    }

    SAFEPOINTER(instance, new FreshFlower(name, k, b, t), return nullptr);

    SAFEPOINTER(data, new fdata, return nullptr);

    *data = instance->get_data();

    SafeReleaseNULL(instance);

    return data;
}

sqlfscore* getscoredata(const char* name, fdata* flower_data, int sqlnum) {
    sqlfscore* data;
    DriedFlower* instance;

    if (!flower_data || !name) {
        return nullptr;
    }

    SAFEPOINTER(instance, new DriedFlower(name, *flower_data), return nullptr);

    SAFEPOINTER(data, new sqlfscore, return nullptr);

    *data = instance->get_score(sqlnum);

    SafeReleaseNULL(instance);

    return data;
}

void release_score_data(sqlfscore* data) {
    SafeReleaseNULL(data);
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

int readdata(int num, sqlfscore* data) {
    return sqlins->readdata(num, data);
}

int writedata(sqlfscore* data) {
    return sqlins->writedata(data);
}

int deletedata(int num) {
    return sqlins->deletedata(num);
}

int getsize() {
    return sqlins->getsize();
}
