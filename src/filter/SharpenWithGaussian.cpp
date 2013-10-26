//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SharpenWithGaussian.h"

using namespace cv;

cv::Mat SharpenWithGaussian::transform(cv::Mat image) {
    double t = (double)getTickCount();
    cv::Mat result;
    cv::GaussianBlur(image, result, cv::Size(0, 0), 9);
    cv::addWeighted(image, 1.5, result, -0.5, 0, result);

    t = ((double)getTickCount() - t)/getTickFrequency();
    char a[100];
    sprintf(a, "Sharpened in %fs", t);
    cv::putText(result, a, cvPoint(10,20), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0,0,0), 1, CV_AA);
    return result;
}
