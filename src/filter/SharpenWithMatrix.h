//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __SharpenWithMatrix_H_
#define __SharpenWithMatrix_H_


class SharpenWithMatrix : public Transformation {

public:
    float mult;

    SharpenWithMatrix();

    virtual cv::Mat transform(cv::Mat image);
};


#endif //__SharpenWithMatrix_H_
