//
// Created by Kuba Sławiński on 17/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#ifndef __Transformation_H_
#define __Transformation_H_

#include <opencv/cv.h>

class Transformation {
public:
    virtual cv::Mat transform(cv::Mat image) = 0;

    virtual ~Transformation() = 0;
};


#endif //__Transformation_H_
