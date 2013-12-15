//
// Created by Kuba Sławiński on 13/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "FindLines.h"
#include "Util.h"

using namespace cv;

cv::Mat FindLines::transform(cv::Mat image) {
    Mat result;
    Mat resultCanny;
    Mat resultLines = Mat::zeros(image.size(), image.type());
    if (blurRadius > 0)
        GaussianBlur(image, result, cv::Size(0, 0), blurRadius);
    else
        image.copyTo(result);

    Canny(result, result, 50, 200, 3);

    vector<Vec4i> lines;
    HoughLinesP(result, lines, rho, theta, thresh, minLineLength, maxLineGap);
    cvtColor(result, resultCanny, CV_GRAY2RGB);
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(resultLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(1, 55, 55), 3, CV_AA);
        line(resultLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(1, 255, 255), 1, CV_AA);
    }

    Util::addAlphaMat(resultCanny, image, 0.3);
    Util::addAlphaMat(resultLines, image, 0.8);
    return image;
//    return transparent;
}

FindLines::FindLines() {
    blurRadius = 1;
    rho = 1;
    theta = CV_PI/ 180;
    thresh = 50;
    minLineLength = 5;
    maxLineGap = 10;
}