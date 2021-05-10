//
//  DynamicCast.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/4/27.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef DynamicCast_h
#define DynamicCast_h

#include "FreshFlower.hpp"

using namespace std; //NOLINT

/* This file declared some global data and main functions.*/
#if __cplusplus
extern "C" {
#endif

static fdata basedata;
FreshFlower* preins;
FreshFlower* nowins;
condition_variable cvar;
    
int cast(int argc, char **argv);

// for command debug
int main(int argc, char **argv);

void myfunc(void);
void releasesource();
void detectargs(int argc, char **argv);
#ifdef __cplusplus
}
#endif

#endif /* DynamicCast_h */
