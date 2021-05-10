//
//  FreshFlower.cpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/9.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#include "FreshFlower.hpp"

FreshFlower::FreshFlower(const char* name, int k, int b) : super(name) {
    haswritten_havg = false;
    
    data.k = k;
    
    data.b = b;
    
    data.time = super::time;
    
    hsvins = super::imgnobg_hsv.clone();
    
    thread t(&FreshFlower::prase_h_average, this, ref(data.h_average));

    t.detach();
}

FreshFlower::~FreshFlower(){
    
}

void FreshFlower::prase_h_average(double& h_average) {
    super::prase_h_average(h_average);
    
    haswritten_havg = true;
}
