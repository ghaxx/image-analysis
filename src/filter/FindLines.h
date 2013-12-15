//
// Created by Kuba Sławiński on 13/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __FindLines_H_
#define __FindLines_H_


class FindLines : public Transformation {

public:

    FindLines();

    virtual cv::Mat transform(cv::Mat image);

    double blurRadius;
    double rho;
    double theta;
    int thresh;
    double minLineLength;
    double maxLineGap;
};


#endif //__FindLines_H_
