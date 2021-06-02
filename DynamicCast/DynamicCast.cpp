//
//  DynamicCast.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/4/27.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

/* BSD 3-Clause License
 
   Copyright (c) 2021, penghubingzhou
   All rights reserved.
 
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 
   1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 
   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 
   3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
 
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "DynamicCast.h"
#include <future>

#define LEN 6

int main(int argc, char **argv) {
    return cast(argc, argv);
}

int cast(int argc, char **argv) {
    fdata* dataptr;
    future<sqlfscore*> score[LEN];
    chrono::milliseconds span(100);
    sqlfscore* ptr[LEN];
    const char* runpath = "/Users/penghubingzhou/Desktop/整理/20210513/%d.jpg";
    const char* basepath = "/Users/penghubingzhou/Desktop/整理/20210513/based.jpg";

    if (DynamicCast_init("/Users/penghubingzhou/Desktop/Database.db")) {
        return -1;
    }

    dataptr = getbasedata(basepath, -0.46, 13.67, 21);

    if (!dataptr) {
        return -1;
    }

    basic_data = *dataptr;

    for (int i = 0; i < LEN; i++) {
        const char* path;

        path = sqlite3_mprintf(runpath, i + 1);

        score[i] = async(getscoredata, path, &basic_data, 4 + i);
    }

    for (int i = 0; i < LEN; i++) {
        while (score[i].wait_for(span) != future_status::ready) {
            continue;
        }
    }

    for (int i = 0; i < LEN; i++) {
        ptr[i] = score[i].get();

        writedata(ptr[i]);

        // release_score_data(ptr[i]);
    }

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

void DynamicCast_deinit() {
    SafeReleaseNULL(sqlins);
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
