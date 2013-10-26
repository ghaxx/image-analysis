//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __Lightness_H_
#define __Lightness_H_


class Lightness : public Transformation {

public:
    virtual cv::Mat transform(cv::Mat image);
};


#endif //__Lightness_H_
