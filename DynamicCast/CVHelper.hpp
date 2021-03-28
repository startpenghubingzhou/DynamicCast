//
//  CVHelper.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/3/17.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef CVHelper_hpp
#define CVHelper_hpp

#include "Basedefs.h"

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>


using namespace std; //NOLINT
using namespace cv; //NOLINT

/*!
 * @class CVHelper
 *
 * @abstract The helper class to handle JPEG
 * data with libjpeg
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
     * @param filename An const char that contained the file path.
     *
     * @discussion
     * This function will be executed automatically
     * as this class is created. This function will
     * call the API of OpenCV and create the
     * Mat object.
     * Please do not call this function directly, use
     * "new" operator instead.
     */
    explicit CVHelper(const char* filename);

    /*!
     * @function ~CVHelper
     *
     * @abstract
     * The destructor of CVHelper, release all the
     * sources that the class uses
     *
     * @discussion
     * This function will be executed automatically
     * as this class will be released. This function will
     * call the API of libjpeg-turbo and destroy all source
     * this class has decleared.
     * Please do not call this function directly, use "delete"
     * operator instead.
     */
    ~CVHelper();

    /*!
     * @function prasecolor_pixel
     *
     * @abstract
     * Create the RGB data of file.
     *
     * @discussion
     * This function will automatically create the RGB data
     * of image using OpenCV APIs and copy it to the interal
     * buffer. When you have created the CVHelper instance
     * successfully, you should call this function firstly
     * to create the RGB data.
     *
     * @result Returns true if succeeed, or false.
     */

    string prasecolor_pixel();

 private:
    Mat image;

    Mat imgnobg_hsv;

    colornum num_flowers = {0};

    bool hsvinrange(hsvdata pixel, colorrange range);
};

#endif /* CVHelper_hpp */
