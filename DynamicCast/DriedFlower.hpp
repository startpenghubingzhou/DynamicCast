//
//  DriedFlower.hpp
//  DynamicCast
//
//  Created by penghubingzhou on 2021/5/11.
//  Copyright © 2021 penghubingzhou. All rights reserved.
//

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
    void prase_data(basedata& mydata) override;

    int calculate_area_flower(Mat& image);

    ddata data;

    Mat hsvins;
};

#endif /* DriedFlower_hpp */
