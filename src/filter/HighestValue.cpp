//
// Created by Kuba Sławiński on 17/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "HighestValue.h"

using namespace cv;

cv::Mat HighestValue::transform(cv::Mat image) {

    Mat result(image);
    for (int x = 0; x < image.cols; x++) {
        for (int y = 0; y < image.rows; y++) {
            float max = 0;
            for (int c = 0; c < image.channels(); c++)
                if (max < image.at<Vec3b>(y, x)[c])
                    max = image.at<Vec3b>(y, x)[c];

            for (int c = 0; c < image.channels(); c++)
                result.at<Vec3b>(y, x)[c] = max;
        }
    }
    return result;
}
