//
//  Basedefs.h
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/28.
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

#ifndef Basedefs_h
#define Basedefs_h

#include <sys/stat.h>
#include <math.h>
#include <stdlib.h>

/* This files included all the definations and structures
   that the project used. */
#define FUNCNAME "DynamicCast"  // Funcion name
#define VNAME(a) (#a)  // Variable name

// small region defination
#define AERA_SMALL 200

// threshold value defination
#define THRESHOLD_MIN 0
#define THRESHOLD_MAX 255

// max date len for sql
#define DATELEN 3 * sizeof(int) + 3

// grade define
#define GRADE_UNKNOWN 0
#define GRADE_ONE 1
#define GRADE_TWO 2
#define GRADE_THREE 3
#define GRADE_FOUR 4
#define GRADE_FIVE 5

// SQLFriend Flags
#define SQLF_OK 0
#define SQLF_FAILED -1

// determine if the number in range
#define INRANGE(a, b, c) ((b >= a) && (b <= c))
#define INRANGE_SCORE(a, b, c) ((b >= a) && (b < c))

// Score calculation
#define CAL_PERCENT(percent) 100.000 * (1.000 - static_cast<double>(percent))
#define CAL_FINAL(brown, dry, trans, fade) static_cast<double>(brown * 0.4 + dry * 0.3 + trans * 0.2 + fade * 0.1)
#define CAL_TRANSRATIO(x, y) static_cast<double>(abs(x - y) / 180.000)
#define CAL_DRYSCORE(dryratio) dryratio <= 1.000 ? (70 - 30 * static_cast<double>(dryratio)) : 0
#define CAL_DRYRATIO(daysavg, days) ((static_cast<double>(days) - static_cast<double>(daysavg)) / static_cast<double>(daysavg))
#define CAL_DAYAVG(k, b, t) ceil(k * t + b)
#define CAL_DAYS(time_pre, time_now) ceil(difftime(time_now, time_pre) / (60 * 60 * 24))

#define CAL_RECURAVG(preavg, add, num) ((num - 1) * preavg + add) / num

// Format printf
#define funcprint(fmt, a...)                                \
do {                                                        \
    printf("%s::" fmt, FUNCNAME, ##a);                      \
}while(0)

// Safe pointer allocation
#define SAFEPOINTER(a, op_alloc, op_failed)                 \
a = op_alloc;                                               \
                                                            \
if (!a) {                                                   \
    funcprint("got a null pointer named: %s!\n", VNAME(a)); \
    op_failed;                                              \
}

// Safe release macro, based on OSSafeReleaseNULL
#define SafeReleaseNULL(ptr)                                \
do {                                                        \
    if (ptr) {                                              \
        delete ptr;                                         \
        ptr = nullptr;                                      \
    }                                                       \
}while (0)

/* cvhelper_flag: a enum that described the class defination of
   a instance of CVhelper */
typedef enum cvhelper_flag {
    pic_fresh = 0,
    pic_dried = 1
}helperflag;

// color_range: a struct that described the range of a color in HSV space
typedef struct color_range {
    int h_min;
    int h_max;
    int s_min;
    int s_max;
    int v_min;
    int v_max;
}colorrange;

// color_range_hsv: a struct containing the range data of colors in HSV space
struct color_range_hsv {
    colorrange pink;
    colorrange black;
    colorrange gray;
    colorrange white;
    colorrange red1;
    colorrange red2;
    colorrange orange;
    colorrange yellow;
    colorrange green;
    colorrange cyan;
    colorrange blue;
    colorrange purple;
};

static struct color_range_hsv hsvrange = {
    {160, 180, 0, 255, 0, 255},
    {0, 180, 0, 255, 0, 46},
    {0, 180, 0, 43, 46, 220},
    {0, 180, 0, 30, 221, 255},
    {156, 180, 43, 255, 46, 255},
    {0, 10, 43, 255, 46, 255},
    {11, 25, 43, 255, 46, 255},
    {26, 34, 43, 255, 46, 255},
    {35, 77, 43, 255, 46, 255},
    {78, 99, 43, 255, 46, 255},
    {100, 124, 43, 255, 46, 255},
    {122, 155, 43, 255, 46, 255}
};

// hsv_pixel_data: a struct that described the hsv data for one pixel
typedef struct hsv_pixel_data {
    uint8_t h, s, v;
    uint8_t color;
}hsvdata;

/* num_of_the_color: a struct that described the number of pixels every
   image having with the flower */
typedef struct num_of_the_color {
    int pink, white, red, green, blue, purple;
}colornum;

/* hsv_color_loaction: a enum that described the location of every colors
   in num_of_the_color */
typedef enum hsv_color_loaction {
    loc_pink = 0,
    loc_white = 1,
    loc_red = 2,
    loc_green = 3,
    loc_blue = 4,
    loc_purple = 5
}loc_color;

/* core_calulate_data: a struct containing the data to calculate the score
   of a flower */
typedef struct score_calulate_data {
    double k, b;
    int t;
    double percent_brown;
    double percent_trans;
    double percent_fade;
    double percent_drytime;
} dscore;

/* flower_score: a struct containing the data of the flower
   that will be written to the database. */
typedef struct flower_score {
    double browningscore;
    double drytimescore;
    double transferredscore;
    double fadescore;
    double finalscore;
    uint8_t grade;
}fscore;

/* Fresh_flower_data: a struct containing the neccesary data
   of a fresh flower. */
typedef struct fresh_flower_data {
    double k, b, t;
    time_t time;
    double h_average;
    int color;
}fdata;

/* Dried_flower_data: a struct containing the neccesary data
 of a dried flower. */
typedef struct dried_flower_data {
    uint32_t s_flower;
    uint32_t s_browning;
    uint32_t s_fade;
    double h_average;
    time_t time;
}ddata;

/* flower_data: a struct containing the data of the flower
 that will be written to the database. */
typedef struct flower_data_sql {
    fscore score;
    char time[15];
    char name[1024];
    int num;
}sqlfscore;
#endif /* Basedefs_h */
