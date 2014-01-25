//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include <opencv2/highgui/highgui.hpp>
#include "MoGMotionDetection.h"
#include "Util.h"

using namespace cv;

cv::Mat MoGMotionDetection::transform(Mat image) {
    Mat result(image.rows, image.cols * 2, image.type());
    Mat background;
    Mat foregroundMask;
    Mat foreground = Mat::zeros(image.rows, image.cols, image.type());
    backgroundSubtractorMOG2->operator()(image, foregroundMask, -1);
    backgroundSubtractorMOG2->getBackgroundImage(background);
    Util::pictureInPicture(background, result, 0, 0, image.cols, image.rows);


    GaussianBlur(foregroundMask, foregroundMask, cv::Size(0, 0), 3);
    cv::threshold(foregroundMask, foregroundMask, 0, 255, CV_THRESH_BINARY | THRESH_OTSU);
    morphologyEx(foregroundMask, foregroundMask, MORPH_OPEN, getStructuringElement(MORPH_ELLIPSE, Size(7, 7)));
//    image.copyTo(foreground, foregroundMask);
//    Util::pictureInPicture(foreground, result, image.cols, 0, image.cols, image.rows);

    Mat canny_output;

    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    Canny(foregroundMask, canny_output, 100, 100 * 2, 3);
    /// Find contours
    findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

    /// Draw contours
    Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
    for (int i = 0; i < contours.size(); i++) {
        Scalar color = Scalar(255, 255, 255);
        drawContours(image, contours, i, color, 2, 8, hierarchy, 0, Point());
        drawContours(image, contours, i, Scalar(0, 0, 0), 1, 8, hierarchy, 0, Point());
    }

    Util::pictureInPicture(image, result, image.cols, 0, image.cols, image.rows);
    return result;
}

MoGMotionDetection::MoGMotionDetection() {
    history = 30;
    nMixtures = 4;
    threshold = 4;
    backgroundRatio = 0.5;
    _backgroundRatio = (int) (backgroundRatio * 100);
    _threshold = (int) threshold;
    backgroundSubtractorMOG2 = new BackgroundSubtractorMOG2(history, threshold, true);
}


void MoGMotionDetection::createControls(const std::string &windowTitle) {
    string suffix = " - controls";
    namedWindow(windowTitle + suffix);
    imshow(windowTitle + suffix, Mat::zeros(1, 500, CV_8UC1));

    createTrackbar("History", windowTitle + suffix, &history, 30, MoGMotionDetection::onChange1, this);
    createTrackbar("Var Threshold", windowTitle + suffix, &_threshold, 100, MoGMotionDetection::onChange4, this);
//    createTrackbar("nMixtures", windowTitle, &nMixtures, 10, MoGMotionDetection::onChange2, this);
//    createTrackbar("Background Ratio", windowTitle, &_backgroundRatio, 100, MoGMotionDetection::onChange3, this);
}


void MoGMotionDetection::onChange1(int c, void *p) {
    MoGMotionDetection *w = (MoGMotionDetection *) p;
    w->reset();
}

void MoGMotionDetection::onChange2(int c, void *p) {
    MoGMotionDetection *w = (MoGMotionDetection *) p;
    w->reset();
}

void MoGMotionDetection::onChange3(int c, void *p) {
    MoGMotionDetection *w = (MoGMotionDetection *) p;
    w->backgroundRatio = (double) w->_backgroundRatio / 100;
    w->reset();
}

void MoGMotionDetection::onChange4(int c, void *p) {
    MoGMotionDetection *w = (MoGMotionDetection *) p;
    w->threshold = (float) w->_threshold;
    w->reset();
}

void MoGMotionDetection::reset() {
    delete backgroundSubtractorMOG2;
//    backgroundSubtractorMOG = new BackgroundSubtractorMOG(history, nMixtures, backgroundRatio);
    backgroundSubtractorMOG2 = new BackgroundSubtractorMOG2(history, threshold, true);
}
