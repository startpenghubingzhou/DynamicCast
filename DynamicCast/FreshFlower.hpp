//
//  FreshFlower.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/9.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

#ifndef FreshFlower_hpp
#define FreshFlower_hpp

#include <thread>
#include "CVHelper.hpp"
#include "Basedefs.h"
#include <future>


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
     * @param k an integer that contained the k value.
     *
     * @param b an integer that contained the b value.
     *
     * @discussion
     * This function will be executed automatically
     * as this class is instantiated. This function will
     * automatically be constructed with CVHelper constructor.
     */
    explicit FreshFlower(const char* name, int k, int b);

    /*!
     * @function ~FreshFlower
     *
     * @abstract
     * The destructor of FreshFlower, release all the
     * sources that the class uses
     */
    ~FreshFlower();
    
    /*!
     * @function prase_h_average
     *
     * @abstract
     * prase the h average data in the image.
     *
     * @param h_average the double data to
     * contain the average data.
     *
     * @discussion
     * see @CVHelper/prase_h_average
     *
     */
    virtual void prase_h_average(double& h_average) override;
    
    fdata data;
    
    bool haswritten_havg;
    
 private:
    future<double> future_havg;
    
    promise<double> promise_havg;
    
    Mutex lock;

    Mat hsvins;
};

#endif /* FreshFlower_hpp */
