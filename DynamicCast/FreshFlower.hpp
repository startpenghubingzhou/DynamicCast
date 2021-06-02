//
//  FreshFlower.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/9.
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

#ifndef FreshFlower_hpp
#define FreshFlower_hpp

#include "Basedefs.h"

#include "CVHelper.hpp"

#define super CVHelper

/*!
 * @class FreshFlower
 *
 * @abstract The class to handle the
 * picture data of the fresh flowers
 * with OpenCV
 *
 * @discussion
 * This class is an helper class to process
 * image of the the fresh flowers. Based on
 * CVHelper
 */

class FreshFlower : public CVHelper{
 public:
    /*!
     * @function FreshFlower
     *
     * @abstract
     * The constructor of FreshFlower, initializes
     * the function of the class
     *
     * @param name a const char that contained the file path.
     *
     * @param k a double that contained the k value.
     *
     * @param b a double that contained the b value.
     *
     * @param t a double that contained the average
     * temperature value.
     *
     * @discussion
     * This function will be executed automatically
     * as this class is instantiated. This function will
     * automatically be constructed with CVHelper constructor.
     */
    explicit FreshFlower(const char* name, double k, double b, double t);

    /*!
     * @function ~FreshFlower
     *
     * @abstract
     * The destructor of FreshFlower, release all the
     * sources that the class uses
     */
    ~FreshFlower();

    /*!
     * @function get_data
     *
     * @abstract
     * get the h average data in the image.
     *
     * @discussion
     * this func can get the base data of a
     * fresh flower instance for the future
     * calculation. Once you have initialized
     * an instance,  you could use this func
     * to get it.
     *
     * @return a fdata struct containing the
     * initialized fresh flower data.
     */
    fdata get_data();

 private:
    virtual void prase_data(basedata& mydata) override;

    fdata data;
};

#endif /* FreshFlower_hpp */
