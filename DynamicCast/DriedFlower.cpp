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
    data.time = super::time;
}

DriedFlower::~DriedFlower() {
    super::~super();
}

void DriedFlower::prase_data(basedata& mydata) {
    super::prase_data(mydata);
}

int DriedFlower::calculate_area_flower(Mat& image) {
    int area;
    Mat tmp;
    Mat labels, stats, centroids, img_color;  // tmp mat for connectedComponentsWithStats
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
