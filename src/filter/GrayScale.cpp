//
// Created by Kuba Sławiński on 17/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "GrayScale.h"

cv::Mat GrayScale::transform(cv::Mat image) {
    cv::Mat grayScale;
    cvtColor(image, grayScale, CV_RGB2GRAY);
    return grayScale;
}
