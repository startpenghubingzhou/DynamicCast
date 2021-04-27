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
    string path = filename;

    image = imread(path);

    // judge the image is empty
    if (image.empty()) {
        funcprint("could not convert image!\n");
        delete this;
        return;
    }
}

CVHelper::~CVHelper() {
}

void CVHelper::convert_hsv() {
    Rect rect;
    Mat result;
    Mat bgModel, fgModel;
    Mat* tmp;
    Mat tmp2;

    rect.width = image.rows;
    rect.height = image.cols;

    // use grabcut to cut the background
    grabCut(image, result, rect, bgModel, fgModel, 5, GC_INIT_WITH_RECT);
    compare(result, GC_PR_FGD, result, CMP_EQ);

    SAFEPOINTER(tmp, new Mat(image.size(), CV_8UC3, Scalar(255, 255, 255)), return);

    image.copyTo(*tmp, result);

    cvtColor(*tmp, tmp2, COLOR_BGR2HSV);

    imgnobg_hsv = tmp2.clone();

    SafeReleaseNULL(tmp);
}

void CVHelper::prasecolor_pixel(promise<double>* instance) {
    string name = "unknown";
    int* numptr = reinterpret_cast<int*>(&num_flowers);
    int loc = loc_pink;
    hsvdata data;
    vector<hsvdata> picdata;
    uint64_t hfull = 0;
    uint64_t num;
    uint64_t havg;

    bool isbackground = false;

    convert_hsv();

    // lock this fucnction until it set value to the promise instance
    lock.try_lock();

    for (int i = 0; i < imgnobg_hsv.rows; i++) {
        for (int j = 0; j < imgnobg_hsv.cols; j++) {
            data.h = imgnobg_hsv.at<Vec3b>(i, j)[0];
            data.s = imgnobg_hsv.at<Vec3b>(i, j)[1];
            data.v = imgnobg_hsv.at<Vec3b>(i, j)[2];

            // Now we will determine the pixel color
            if (hsvinrange(data, hsvrange.pink)) {
                data.color = loc_pink;
                num_flowers.pink++;
            } else if (hsvinrange(data, hsvrange.white)) {
                /* The white pixel may be the background, so
                we should ignore them */
                if (data.h != 0 || data.s != 0 || data.v != 255) {
                    data.color = loc_white;
                    num_flowers.white++;
                    isbackground = false;
                } else {
                    isbackground = true;
                }
            } else if (hsvinrange(data, hsvrange.red1) || hsvinrange(data, hsvrange.red2)) {
                data.color = loc_red;
                num_flowers.red++;
            } else if (hsvinrange(data, hsvrange.green)) {
                data.color = loc_green;
                num_flowers.green++;
            } else if (hsvinrange(data, hsvrange.blue)) {
                data.color = loc_blue;
                num_flowers.blue++;
            } else if (hsvinrange(data, hsvrange.purple)) {
                data.color = loc_purple;
                num_flowers.purple++;
            } else {
                continue;
            }

            // if not background pixel, we should push it in the vector.
            if (!isbackground) {
                picdata.push_back(data);
            }
        }
    }

    // Now that we have detected all the pixels, we will compare with the nums
    for (int i = 0; i < 5; i++) {
        int a = numptr[i];
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
        if (loc == loc_pink && (picdata[num].color == loc_pink || picdata[num].color == loc_red)) {
            hfull += picdata[num].h;
        } else if (picdata[num].color == loc) {
            hfull += picdata[num].h;
        }
    }

    havg = hfull / num;

    funcprint("the flower's color is: %s, the h average data is : %llu\n", name.c_str(), havg);

    instance->set_value(havg);

    // unlock the function since we have set value
    lock.unlock();
}

fscore* CVHelper::generate_score(dscore* src) {
    fscore* score_data;

    SAFEPOINTER(score_data, new fscore, return nullptr)

    score_data->drytimescore = CAL_DRY(CAL_DRYRATIO(src->k, src->b, src->t));
    score_data->transferredscore = CAL_PERCENT(src->percent_trans);
    score_data->browningscore = CAL_PERCENT(src->percent_brown);
    score_data->fadescore = CAL_PERCENT(src->percent_fade);
    score_data->finalscore = CAL_FINAL(score_data->browningscore, score_data->drytimescore, score_data->transferredscore, score_data->fadescore);

    return score_data;
}

bool CVHelper::hsvinrange(hsvdata pixel, colorrange range) {
    return INRANGE(range.h_min, pixel.h, range.h_max) &&
    INRANGE(range.s_min, pixel.s, range.s_max) &&
    INRANGE(range.v_min, pixel.v, range.v_max);
}

