//
// Created by Kuba Sławiński on 17/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#ifndef __GrayScale_H_
#define __GrayScale_H_

#import "Transformation.h"

class GrayScale : public Transformation {

public:
    virtual cv::Mat transform(cv::Mat image);
};


#endif //__GrayScale_H_
