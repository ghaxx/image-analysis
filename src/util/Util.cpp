//
// Created by Kuba Sławiński on 10/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Util.h"

using namespace cv;

string Util::intToString(int number) {
    std::stringstream ss;
    ss << number;
    return ss.str();
}

void Util::pictureInPicture(Mat &source, Mat &destination, int x, int y, int w, int h) {
    Mat small;
    resize(source, small, Size(w, h));
    Mat subView = destination(Rect(x, y, small.cols, small.rows));
    if (small.type() != destination.type())
        cvtColor(small, small, CV_GRAY2RGB);
    small.copyTo(subView);
}

void Util::addAlphaMat(Mat &src, Mat &dst, double alpha) {
    for (int x = 0; x < dst.cols; x++) {
        for (int y = 0; y < dst.rows; y++) {
            if (src.at<Vec3b>(y, x)[0] != 0)
                for (int c = 0; c < dst.channels(); c++) {
                    double v = ((1 - alpha) * dst.at<Vec3b>(y, x)[c]) + ((alpha) * src.at<Vec3b>(y, x)[c]);
                    dst.at<Vec3b>(y, x)[c] = max(0.0, min(v, 255.0));
                }
        }
    }
}

void Util::addAlphaMat(Mat &src, Mat &dst) {
    for (int x = 0; x < dst.cols; x++) {
        for (int y = 0; y < dst.rows; y++) {
            if (src.at<Vec3b>(y, x)[3] != 0)
                for (int c = 0; c < dst.channels(); c++) {
                    double alpha = (double) src.at<Vec4b>(y, x)[3] / 255;
                    double v = ((1.0 - alpha) * dst.at<Vec3b>(y, x)[c]) + ((alpha) * src.at<Vec4b>(y, x)[c]);
                    dst.at<Vec3b>(y, x)[c] = max(0.0, min(v, 255.0));
                }
        }
    }
}