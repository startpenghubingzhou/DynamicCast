//
//  Basedefs.h
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/28.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef Basedefs_h
#define Basedefs_h

#include <iostream>
#include <sys/stat.h>
#include <math.h>
#include <atomic>

/* This files included all the definations and structures
   that the project used. */
#define FUNCNAME "DynamicCast"  // Funcion name
#define VNAME(a) (#a)  // Variable name

// determine if the number in range
#define INRANGE(a, b, c) ((b >= a) && (b <= c))

// Score calculation
#define CAL_PERCENT(percent) 100 * (1 - percent)
#define CAL_FINAL(brown, dry, trans, fade) brown * 0.4 + dry * 0.3 + trans * 0.2 + fade * 0.1
#define CAL_TRANSRATIO(x, y) abs(x - y) / 180
#define CAL_DRY(dryratio) dryratio <= 1 ? (70 - 30 * dryratio) : 0
#define CAL_DRYRATIO(k, b, t) ceil(k * t + b)
#define CAL_DAYS(time_pre, time_now) ceil(difftime(time_pre, time_now) / (60 * 60 * 24))

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
static struct color_range_hsv {
    colorrange pink = {160, 180, 0, 255, 0, 255};
    colorrange black = {0, 180, 0, 255, 0, 46};
    colorrange gray = {0, 180, 0, 43, 46, 220};
    colorrange white = {0, 180, 0, 30, 221, 255};
    colorrange red1 = {156, 180, 43, 255, 46, 255};
    colorrange red2 = {0, 10, 43, 255, 46, 255};
    colorrange orange = {11, 25, 43, 255, 46, 255};
    colorrange yellow = {26, 34, 43, 255, 46, 255};
    colorrange green = {35, 77, 43, 255, 46, 255};
    colorrange cyan = {78, 99, 43, 255, 46, 255};
    colorrange blue = {100, 124, 43, 255, 46, 255};
    colorrange purple = {122, 155, 43, 255, 46, 255};
}hsvrange;

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
    uint8_t browningscore;
    uint8_t drytimescore;
    uint8_t transferredscore;
    uint8_t fadescore;
    uint8_t finalscore;
    uint8_t grade;
}fscore;

typedef struct fresh_flower_data{
    int k, b;
    time_t time;
    double h_average;
}fdata;

typedef struct dried_flower_data{
    uint64_t s_flower;
    uint64_t s_browning;
    uint64_t s_fade;
    double h_average;
    time_t time;
}ddata;
#endif /* Basedefs_h */
