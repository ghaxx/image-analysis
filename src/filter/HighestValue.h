//
// Created by Kuba Sławiński on 17/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//




#ifndef __HighestValue_H_
#define __HighestValue_H_

#import "Transformation.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>

class HighestValue : public Transformation {

public:

    virtual cv::Mat transform(cv::Mat image);
};


#endif //__HighestValue_H_
