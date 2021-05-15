//
//  FreshFlower.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/9.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

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
     * @discussion
     * This function will be executed automatically
     * as this class is instantiated. This function will
     * automatically be constructed with CVHelper constructor.
     */
    explicit FreshFlower(const char* name, double k, double b);

    /*!
     * @function ~FreshFlower
     *
     * @abstract
     * The destructor of FreshFlower, release all the
     * sources that the class uses
     */
    ~FreshFlower();

    /*!
     * @function prase_data
     *
     * @abstract
     * prase the h average data in the image.
     *
     * @param mydata the basedata struct to
     * contain the base data.
     *
     * @discussion
     * see @CVHelper/prase_data
     *
     */
    virtual void prase_data(basedata& mydata) override;

    fdata get_data();

 private:
    fdata data;

    Mat hsvins;
};

#endif /* FreshFlower_hpp */
