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

#include <future> //NOLINT

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
     * prase the color data of the image.
     *
     * @discussion
     * This function will automatically prase the HSV data
     * of image using OpenCV APIs and get the color that the
     * run this function to get the color of the flower. It
     * will write data into a promise with a thread, so you
     * should use a thread to create and execute it.
     */

    void prasecolor_pixel(promise<double>* instance);

 private:
    Mat image;

    Mat imgnobg_hsv;

    colornum num_flowers = {0, 0, 0, 0, 0, 0};

    thread* cut;

    Mutex lock;

    fscore* generate_score(dscore* src);

    bool hsvinrange(hsvdata pixel, colorrange range);

    void convert_hsv();

    double prase_brown();

    double prase_trans();

    double prase_fade();

    double prase_drytime();
};

#endif /* CVHelper_hpp */
