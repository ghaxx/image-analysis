//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __HaarFaceTransformation_H_
#define __HaarFaceTransformation_H_


class HaarFaceTransformation : public Transformation {
    cv::CascadeClassifier *classifier;
public:
    double scaleFactor;
    int minNeighbors;
    cv::Size minSize;

    HaarFaceTransformation();

    virtual cv::Mat transform(cv::Mat image);
};


#endif //__HaarFaceTransformation_H_
