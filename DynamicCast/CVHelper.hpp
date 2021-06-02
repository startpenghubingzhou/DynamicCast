//
//  CVHelper.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/17.
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

#ifndef CVHelper_hpp
#define CVHelper_hpp

#include "Basedefs.h"

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

/* basedata: a struct containing the based data
   that the subclass instances may use. Defined
   it here since it use cpp type */
typedef struct cvhelper_based_data {
    Mat imghsv;
    double h_average;
    double color;
}basedata;

/*!
 * @class CVHelper
 *
 * @abstract The helper class to handle JPEG
 * data with OpenCV
 *
 * @discussion
 * This class is an helper class to process
 * image. It will use OpenCV to process.
 */

class CVHelper{
 public:
    /*!
     * @function CVHelper
     *
     * @abstract
     * The constructor of CVHelper, initializes
     * the function of the class
     *
     * @param filename a const char that contained the file path.
     *
     * @discussion
     * This function will be executed automatically
     * as this class is created. This function will
     * call the API of OpenCV and create the
     * Mat object.
     */
    explicit CVHelper(const char* filename);

    /*!
     * @function ~CVHelper
     *
     * @abstract
     * The destructor of CVHelper, release all the
     * sources that the class uses
     */
    ~CVHelper();

    /*!
     * @function prase_data
     *
     * @abstract
     * prase the base data in an image.
     *
     * @param mydata the basedata struct to
     * contain the base data.
     *
     * @discussion
     * This function will automatically prase the HSV data
     * of image using OpenCV APIs and get the base data of
     * the picture.
     *
     */
    virtual void prase_data(basedata& mydata);

 protected:
    double havg = 0;

    time_t time;

    Mat image;

    colornum num_flowers;

    int loc = loc_pink;

    void convert_hsv(Mat& hsvimage);

    bool hsvinrange(hsvdata pixel, colorrange range);
};

#endif /* CVHelper_hpp */
