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

void Util::pictureInPicture(Mat &source, Mat &destination, int x, int y, int w, int h, int offsetX, int offsetY, int sourceWidth, int sourceHeight) {
    Mat small(source);
    if (sourceWidth == 0)
        sourceWidth = source.cols - offsetX;
    if (sourceHeight == 0)
        sourceHeight = source.rows - offsetY;
    if (offsetX * offsetY != 0) {
        small = small(Rect(offsetX, offsetY, sourceWidth, sourceHeight));
    }
    resize(small, small, Size(w, h));
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

void Util::addFrame(Mat &dest, int width, Scalar &color) {
    line(dest, Point(0, dest.rows), Point(dest.cols, dest.rows), color, width);
    line(dest, Point(0, 0),         Point(dest.cols, 0),         color, width);
    line(dest, Point(0, 0),         Point(0,         dest.rows), color, width);
    line(dest, Point(dest.cols, 0), Point(dest.cols, dest.rows), color, width);
}


void Util::resizeCanvas(Mat &source, Mat &canvas, int width, Scalar &color) {
    Mat tmp = source.clone();
    canvas = Mat::zeros(source.rows + 2 * width, source.cols + 2 * width, source.type());
    pictureInPicture(tmp, canvas, width, width, tmp.cols, tmp.rows);
}

