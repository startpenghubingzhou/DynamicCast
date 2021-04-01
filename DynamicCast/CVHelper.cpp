//
//  CVHelper.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/17.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "CVHelper.hpp"

CVHelper::CVHelper(const char* filename) {
    string path = filename;
    cvtColor(imread(path), image, COLOR_BGR2RGB);

    image = imread(path);

    // judge the image is empty
    if (image.empty()) {
        funcprint("could not find image!\n");
        return;
    }
}

CVHelper::~CVHelper() {
}

void CVHelper::prasecolor_pixel(promise<string>* instance) {
    Rect rect;
    Mat result;
    Mat bgModel, fgModel;
    Mat* tmp;
    string name = "unknown";
    int* numptr = reinterpret_cast<int*>(&num_flowers);
    int loc = 0;
    hsvdata data;
    Mutex mtx;

    // lock this fucnction until it set value to the promise instance
    mtx.lock();

    rect.width = image.rows;
    rect.height = image.cols;

    grabCut(image, result, rect, bgModel, fgModel, 5, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);

    SAFEPOINTER(tmp, new Mat(image.size(), CV_8UC3, Scalar(255, 255, 255)), return);

    image.copyTo(*tmp, result);

    cvtColor(*tmp, imgnobg_hsv, COLOR_BGR2HSV);

    for (int i = 0; i < imgnobg_hsv.rows; i++) {
        for (int j = 0; j < imgnobg_hsv.cols; j++) {
            data.h = imgnobg_hsv.at<Vec3b>(i, j)[0];
            data.s = imgnobg_hsv.at<Vec3b>(i, j)[1];
            data.v = imgnobg_hsv.at<Vec3b>(i, j)[2];

            // Now we will determine the pixel color
            if (hsvinrange(data, hsvrange.pink)) {
                num_flowers.pink++;
            } else if (hsvinrange(data, hsvrange.white)) {
                /* The white pixel may be the background, so
                we should ignore them */
                if (data.h != 0 || data.s != 0 || data.v != 255) {
                    num_flowers.white++;
                }
            } else if (hsvinrange(data, hsvrange.red1) || hsvinrange(data, hsvrange.red2)) {
                num_flowers.red++;
            } else if (hsvinrange(data, hsvrange.green)) {
                num_flowers.green++;
            } else if (hsvinrange(data, hsvrange.blue)) {
                num_flowers.blue++;
            } else if (hsvinrange(data, hsvrange.purple)) {
                num_flowers.purple++;
            } else {
                continue;
            }
        }
    }

    // Now that we have detected all the pixels, we will compare with the nums
    for (int i = 0; i < 5; i++) {
        if (numptr[loc] <= numptr[i + 1]) {
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

    funcprint("the flower's color is: %s\n", name.c_str());

    SafeReleaseNULL(tmp);

    instance->set_value(name);

    // unlock the function since we have set value
    mtx.unlock();
}

bool CVHelper::hsvinrange(hsvdata pixel, colorrange range) {
    return INRANGE(range.h_min, pixel.h, range.h_max) &&
    INRANGE(range.s_min, pixel.s, range.s_max) &&
    INRANGE(range.v_min, pixel.v, range.v_max);
}
