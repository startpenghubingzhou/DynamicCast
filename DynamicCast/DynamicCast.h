//
//  DynamicCast.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/4/27.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

/* BSD 3-Clause License
 
   Copyright (c) 2021, penghubingzhou
   All rights reserved.
 
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
 
   1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.
 
   2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
 
   3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.
 
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
   DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
   SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
   CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
   OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DynamicCast_h
#define DynamicCast_h

#include "FreshFlower.hpp"
#include "DriedFlower.hpp"
#include "SQLFriend.hpp"

using namespace std;

/* This file declared some global data and main functions.*/

static fdata basic_data;
static SQLFriend* sqlins;

// for command debug for test target
int main(int argc, char **argv);
int cast(int argc, char **argv);

// Dynamic library initialization
int DynamicCast_init(const char* dbpath);
void DynamicCast_deinit();

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

const char* testchar();

#endif /* DynamicCast_h */
