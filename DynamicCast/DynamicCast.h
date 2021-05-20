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
#include "DriedFlower.hpp"
#include "SQLFriend.hpp"

using namespace std;

/* This file declared some global data and main functions.*/
#if __cplusplus
extern "C" {
#endif

static fdata basic_data;
static SQLFriend* sqlins;

// for command debug
int main(int argc, char **argv);

// real main func
int cast(int argc, char **argv);
int DynamicCast_init(const char* dbpath);

// DriedFlower func export for Objective-C bridge
sqlfscore* getscoredata(const char* name, fdata* flower_data, int sqlnum);
void release_score_data(sqlfscore* data);

// FreshFlower func export for Objective-C bridge
fdata* getbasedata(const char* name, double k, double b, double t);

// SQLFriend func export for Objective-C bridge
int readdata(int num, sqlfscore* data);
int writedata(sqlfscore* data);
int deletedata(int num);
int getsize();

void myfunc(void);
void releasesource();
void detectargs(int argc, char **argv);

#ifdef __cplusplus
}
#endif

#endif /* DynamicCast_h */
