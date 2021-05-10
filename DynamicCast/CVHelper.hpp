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

#include <future>
#include <opencv2/opencv.hpp>

using namespace std; //NOLINT
using namespace cv; //NOLINT



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
     * @function prase_h_average
     *
     * @abstract
     * prase the h average data in an image.
     *
     * @param h_average the double data to
     * contain the average data.
     *
     * @discussion
     * This function will automatically prase the HSV data
     * of image using OpenCV APIs and get the h average of
     * the picture.
     *
     */
    virtual void prase_h_average(double& h_average);

protected:
    Mat imgnobg_hsv;
    
    double havg = 0;
    
    time_t time;
    
 private:
    Mat image;
    
    colornum num_flowers;
    
    Mutex lock;
    
    bool hsvinrange(hsvdata pixel, colorrange range);

    void convert_hsv();
};

#endif /* CVHelper_hpp */
