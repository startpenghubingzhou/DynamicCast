//
//  DriedFlower.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/11.
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

#ifndef DriedFlower_hpp
#define DriedFlower_hpp

#include "CVHelper.hpp"

#define super CVHelper

class DriedFlower : public super {
 public:
    /*!
     * @function DriedFlower
     *
     * @abstract
     * The constructor of DriedFlower, initializes
     * the function of the class
     *
     * @param name a const char that contained the file path.
     *
     * @param flower_data a Fresh_flower_data struct
     * containing the initialized fresh flower data.
     *
     *
     * @discussion
     * This function will be executed automatically
     * as this class is instantiated. This function will
     * automatically be constructed with CVHelper constructor.
     */
    explicit DriedFlower(const char* name, fdata& flower_data);

    /*!
     * @function ~DriedFlower
     *
     * @abstract
     * The destructor of DriedFlower, release all the
     * sources that the class uses
     */
    ~DriedFlower();

    sqlfscore get_score(int sqlnum);

 private:
    void prase_data(basedata& mydata) override;

    uint32_t calculate_faded(Mat& image);

    uint32_t calculate_area_flower(Mat& image);

    uint32_t calculate_browning(Mat& image);

    fscore __get_score();

    ddata unique_data;

    fdata origin_data;

    const char* sqlpath;

    Mat hsvins;
};

#endif /* DriedFlower_hpp */
