//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Lightness.h"

const double rY = 0.212655;
const double gY = 0.715158;
const double bY = 0.072187;

// Inverse of sRGB "gamma" function. (approx 2.2)
double inv_gam_sRGB(int ic) {
    double c = ic/255.0;
    if ( c <= 0.04045 )
        return c/12.92;
    else
        return pow(((c+0.055)/(1.055)),2.4);
}

// sRGB "gamma" function (approx 2.2)
int gam_sRGB(double v) {
    if(v<=0.0031308)
        v *= 12.92;
    else
        v = 1.055*pow(v,1.0/2.4)-0.055;
    return int(v*255+.5);
}

// GRAY VALUE ("brightness")
int gray(int r, int g, int b) {
    return gam_sRGB(
            rY*inv_gam_sRGB(r) +
            gY*inv_gam_sRGB(g) +
            bY*inv_gam_sRGB(b)
    );
}

cv::Mat Lightness::transform(cv::Mat image) {

    cv::Mat result(image);
    for (int x = 0; x < image.cols; x++) {
        for (int y = 0; y < image.rows; y++) {
            float l =gray(image.at<cv::Vec3b>(y, x)[0], image.at<cv::Vec3b>(y, x)[1], image.at<cv::Vec3b>(y, x)[2]);

            for (int c = 0; c < image.channels(); c++)
                result.at<cv::Vec3b>(y, x)[c] = l;
        }
    }
    return result;
}
