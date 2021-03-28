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

/* This file declared the main function and some global data and functions.*/

CVHelper* based;
CVHelper* test;

void detectargs(int argc, char **argv);
int main(int argc, char **argv);
void releasesource();

#endif /* DynamicCast_hpp */
