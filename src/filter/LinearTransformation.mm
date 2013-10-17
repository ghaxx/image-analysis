//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "LinearTransformation.h"

using namespace cv;

LinearTransformation::LinearTransformation() : Transformation() {
    add = 0;
    mult = 1;
}

cv::Mat LinearTransformation::transform(cv::Mat image) {
    Mat* result = new Mat(image.rows, image.cols, image.type());
    for (int x = 0; x < image.cols; x++) {
        for (int y = 0; y < image.rows; y++) {
            for (int c = 0; c < image.channels(); c++)
                result->at<Vec3b>(y, x)[c] = max(0.0f, min(mult * (add + image.at<Vec3b>(y, x)[c]), 255.0f));
        }
    }
    return *result;
}

