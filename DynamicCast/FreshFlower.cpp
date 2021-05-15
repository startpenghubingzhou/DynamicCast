//
//  FreshFlower.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/9.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "FreshFlower.hpp"

FreshFlower::FreshFlower(const char* name, double k, double b) : super(name) {
    data.k = k;

    data.b = b;

    data.time = super::time;
}

FreshFlower::~FreshFlower() {
    super::~super();
}

void FreshFlower::prase_data(basedata& mydata) {
    super::prase_data(mydata);
}

fdata FreshFlower::get_data() {
    basedata tmp;

    prase_data(tmp);

    data.h_average = tmp.h_average;

    return data;
}
