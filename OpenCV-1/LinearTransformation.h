//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __LinearTransformation_H_
#define __LinearTransformation_H_

#include <iostream>
#include <opencv/cv.h>
#include <opencv/highgui.h>


class LinearTransformation {

    public:
    int add;
    float mult;

    LinearTransformation();
    cv::Mat transform(cv::Mat mat);

};


#endif //__LinearTransformation_H_
