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

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

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
     * @param filename An const char that contained the file path.
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
