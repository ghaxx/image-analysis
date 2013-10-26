//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __SharpenWithGaussian_H_
#define __SharpenWithGaussian_H_


class SharpenWithGaussian : public Transformation {

public:
    virtual cv::Mat transform(cv::Mat image);
};



#endif //__SharpenWithGaussian_H_
