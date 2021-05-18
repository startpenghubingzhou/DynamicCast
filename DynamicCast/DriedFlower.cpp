//
//  DriedFlower.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/11.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "DriedFlower.hpp"
#include <vector>

DriedFlower::DriedFlower(const char* name, fdata& flower_data) : super(name) {
    unique_data.time = super::time;

    origin_data = flower_data;
}

DriedFlower::~DriedFlower() {
    super::~super();
}

void DriedFlower::prase_data(basedata& mydata) {
    super::prase_data(mydata);
}

uint32_t DriedFlower::calculate_faded(Mat& image) {
    uint32_t area;
    colornum data;
    int loc;

    data = super::num_flowers;
    loc = super::loc;

    /* Since it is proved that only green flowers have
       faded, we 'll set this score to 100 for other
       colors.*/

    if (loc != loc_green)
        area = 0;
    else
        area = data.white;

    return area;
}

uint32_t DriedFlower::calculate_browning(Mat& image) {
    Mat labels, stats, centroids, img_color, imgbool;
    vector<Mat> channels;
    int nccomps = 0;
    int area = 0;
    int center;

    split(image, channels);

    imgbool = channels[0].clone();

    // Manual thresholding to screen out the components
    for (int i = 0; i < imgbool.rows; i++) {
        for (int j = 0; j < imgbool.cols; j++) {
            if (imgbool.at<uchar>(i, j) > 0 && imgbool.at<uchar>(i, j) < 30) {
                imgbool.at<uchar>(i, j) = THRESHOLD_MAX;
            } else {
                imgbool.at<uchar>(i, j) = THRESHOLD_MIN;
            }
        }
    }

    nccomps = connectedComponentsWithStats(imgbool, labels, stats, centroids);

    vector<Vec3b> colors(nccomps + 1);

    // background and center pixels remain black.
    colors[0] = Vec3b(0, 0, 0);

    for (int i = 1; i < nccomps; i++) {
        colors[i] = Vec3b(255, 255, 255);

        if (stats.at<int>(i, CC_STAT_AREA) < AERA_SMALL)
            // small regions are painted with black too.
            colors[i] = Vec3b(0, 0, 0);
    }

    /* center pixels is the stamen and may affect
       on the result，so remain it black.*/
    center = labels.at<int>(imgbool.rows / 2, imgbool.cols / 2);

    colors[center] = Vec3b(0, 0, 0);

    img_color = Mat::zeros(imgbool.size(), CV_8UC3);

    for (int i = 0; i < static_cast<int>(colors.size()); i++) {
        if (colors[i] != Vec3b(0, 0, 0)) {
            area += stats.at<int>(i, 4);
        }
    }

    printf("%d\n", area);

    return area;
}

uint32_t DriedFlower::calculate_area_flower(Mat& image) {
    int area;
    Mat tmp;
    Mat labels, stats, centroids;  // tmp mat for connectedComponentsWithStats
    vector<Mat> channels;

    // split the channels of image
    split(image, channels);

    threshold(channels[0], tmp, THRESHOLD_MIN, THRESHOLD_MAX, THRESH_BINARY);

    connectedComponentsWithStats(tmp, labels, stats, centroids);

    /* Since after threshold we have only one component
       with flower, we could simply get the first
       component to calculate the area. */
    area = stats.at<int>(0, 4);

    return area;
}

fscore DriedFlower::get_score() {
    fscore score;
    basedata tmp;
    int days, daysavg;
    double daysratio;

    // fill the unique data area and calculate data
    prase_data(tmp);

    unique_data.h_average = tmp.h_average;

    unique_data.s_flower = calculate_area_flower(tmp.imghsv);

    unique_data.s_browning = calculate_browning(tmp.imghsv);

    unique_data.s_fade = calculate_faded(tmp.imghsv);

    days = CAL_DAYS(origin_data.time, unique_data.time);

    daysavg = CAL_DAYAVG(origin_data.k, origin_data.b, origin_data.t);

    daysratio = CAL_DRYRATIO(daysavg, days);

    // calculate the score data
    score.browningscore = CAL_PERCENT(static_cast<double>(unique_data.s_browning) / static_cast<double>(unique_data.s_flower));

    score.fadescore = CAL_PERCENT(static_cast<double>(unique_data.s_fade / unique_data.s_flower));

    score.transferredscore = CAL_PERCENT(CAL_TRANSRATIO(unique_data.h_average, origin_data.h_average));

    score.drytimescore = CAL_DRYSCORE(daysratio);

    score.finalscore = CAL_FINAL(score.browningscore, score.drytimescore, score.transferredscore, score.fadescore);

    // generate the final grade of the dried flower
    if (INRANGE_SCORE(0, score.finalscore, 50))
        score.grade = GRADE_ONE;
    else if (INRANGE_SCORE(50, score.finalscore, 60))
        score.grade = GRADE_TWO;
    else if (INRANGE_SCORE(60, score.finalscore, 70))
        score.grade = GRADE_THREE;
    else if (INRANGE_SCORE(70, score.finalscore, 80))
        score.grade = GRADE_FOUR;
    else if (INRANGE_SCORE(80, score.finalscore, 100))
        score.grade = GRADE_FIVE;
    else
        score.grade = GRADE_UNKNOWN;

    return score;
}
