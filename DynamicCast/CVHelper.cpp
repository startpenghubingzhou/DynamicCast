//
//  CVHelper.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/17.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "CVHelper.hpp"

#include <string>
#include <vector>

CVHelper::CVHelper(const char* filename) {
    struct stat mystat;

    image = imread(filename);

    // judge the image is empty
    if (image.empty()) {
        funcprint("could not convert image!\n");
        delete this;
        return;
    }

    stat(filename, &mystat);

    time = mystat.st_birthtimespec.tv_sec;
}

CVHelper::~CVHelper() {
}

void CVHelper::convert_hsv(Mat& hsvimage) {
    Rect rect;
    Mat result;
    Mat bgModel, fgModel;
    Mat* tmp;

    rect.width = image.rows;
    rect.height = image.cols;

    // use grabcut to cut the background
    grabCut(image, result, rect, bgModel, fgModel, 5, GC_INIT_WITH_RECT);

    compare(result, GC_PR_FGD, result, CMP_EQ);

    SAFEPOINTER(tmp, new Mat(image.size(), CV_8UC3, Scalar(255, 255, 255)), return);

    image.copyTo(*tmp, result);

    cvtColor(*tmp, hsvimage, COLOR_BGR2HSV);

    SafeReleaseNULL(tmp);
}

void CVHelper::prase_data(basedata& thedata) {
    string name = "unknown";
    int* numptr = reinterpret_cast<int*>(&num_flowers);
    hsvdata data;
    vector<hsvdata> picdata;
    double htmp = 0;
    uint64_t num;
    bool isbackground = false;

    memset(numptr, 0, sizeof(num_flowers));

    convert_hsv(thedata.imghsv);

    for (int i = 0; i < thedata.imghsv.rows; i++) {
        for (int j = 0; j < thedata.imghsv.cols; j++) {
            data.h = thedata.imghsv.at<Vec3b>(i, j)[0];
            data.s = thedata.imghsv.at<Vec3b>(i, j)[1];
            data.v = thedata.imghsv.at<Vec3b>(i, j)[2];

            // Now we will determine the pixel color and set color data
            if (hsvinrange(data, hsvrange.pink)) {
                data.color = loc_pink;
                num_flowers.pink++;
                goto push_vector;
            } else if (hsvinrange(data, hsvrange.white)) {
                /* The white pixel may be the background, so
                we should ignore the background pixel */
                if (data.h != 0 || data.s != 0 || data.v != 255) {
                    data.color = loc_white;
                    num_flowers.white++;
                    goto push_vector;
                } else {
                    isbackground = true;
                    goto push_vector;
                }
            } else if (hsvinrange(data, hsvrange.red1) || hsvinrange(data, hsvrange.red2)) {
                data.color = loc_red;
                num_flowers.red++;
                goto push_vector;
            } else if (hsvinrange(data, hsvrange.green)) {
                data.color = loc_green;
                num_flowers.green++;
                goto push_vector;
            } else if (hsvinrange(data, hsvrange.blue)) {
                data.color = loc_blue;
                num_flowers.blue++;
                goto push_vector;
            } else if (hsvinrange(data, hsvrange.purple)) {
                data.color = loc_purple;
                num_flowers.purple++;
                goto push_vector;
            } else {
                continue;
            }

        push_vector:
            // if not background pixel, we should push it in the vector.
            if (!isbackground) {
                picdata.push_back(data);
            }

            // reset the isbackground flag state
            isbackground = false;
        }
    }

    // Now that we have detected all the pixels, we will compare with the nums
    for (int i = 0; i < 5; i++) {
        int a = numptr[loc];
        int b = numptr[i + 1];

        if (a <= b) {
            loc = i + 1;
        }
    }

    /* Hack: This is a dirty method to detect the pink flower
       cause there's no definite pink range. Will fix it in
       the future. */
    if (loc == loc_red && num_flowers.pink != 0) {
        loc = loc_pink;
    }

    switch (loc) {
        case loc_pink:
            name = "pink";
            break;
        case loc_white:
            name = "white";
            break;
        case loc_red:
            name = "red";
            break;
        case loc_green:
            name = "green";
            break;
        case loc_blue:
            name = "blue";
            break;
        case loc_purple:
            name = "purple";
            break;
        default:
            break;
    }

    for (num = 0; num < picdata.size(); num++) {
        /* Hack: if we identified the flower as pink flower,
           we need to calculate all red and pink data because
           we can take it for granted that the red pixel is pink. */
        if (loc == loc_pink) {
            if (picdata[num].color == loc_pink || picdata[num].color == loc_red) {
                htmp = picdata[num].h;
            }
        } else if (picdata[num].color == loc) {
            htmp = picdata[num].h;
        } else {
            continue;
        }

        /* We use recursive average to calculate the average h
           data because the total h data of a color is so large
           that it can happen to overflow.*/

        if (num == 0) {
            havg = htmp;
        } else {
            havg = CAL_RECURAVG(havg, htmp, num);
        }
    }

    funcprint("the flower's color is: %s, the h average data is : %.3f\n", name.c_str(), havg);

    thedata.h_average = havg;
}

bool CVHelper::hsvinrange(hsvdata pixel, colorrange range) {
    return INRANGE(range.h_min, pixel.h, range.h_max) &&
    INRANGE(range.s_min, pixel.s, range.s_max) &&
    INRANGE(range.v_min, pixel.v, range.v_max);
}
