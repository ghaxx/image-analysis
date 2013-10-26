//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SharpenWithMatrix.h"

using namespace cv;

cv::Mat SharpenWithMatrix::transform(cv::Mat image) {
    Mat result;
    float m[] = {
            -1 * mult,  0, -1 * mult,
             0,  5 * mult,  0,
            -1 * mult,  0, -1 * mult
    };
    Mat kernel = Mat( 3, 3, CV_32F, m );
    cv::filter2D(image, result, image.depth(), kernel);
    return result;
}
