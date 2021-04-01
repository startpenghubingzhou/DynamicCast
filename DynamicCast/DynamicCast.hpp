//
//  DynamicCast.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/20.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef DynamicCast_hpp
#define DynamicCast_hpp

#include "Basedefs.h"

#include <string>
#include "CVHelper.hpp"

using namespace std; //NOLINT

/* This file declared the main function and some global data and functions.*/

CVHelper* pre_pic;
CVHelper* now_pic;
thread* pre_t;
thread* now_t;

void detectargs(int argc, char **argv);
int main(int argc, char **argv);
void releasesource();

#endif /* DynamicCast_hpp */
