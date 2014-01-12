//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MotionDetection11CameraWindow.h"
#include "Util.h"
#include "OpticalFlowMotionDetection.h"

using namespace cv;

MotionDetection11CameraWindow::MotionDetection11CameraWindow(const std::string &title):CameraFilterWindow(title, new OpticalFlowMotionDetection()) {
    maxCorners = getTransformation()->maxCorners;
    qualityLevel = (int) (getTransformation()->qualityLevel * 10000 - 1);
    minDistance = (int) getTransformation()->minDistance;
    
    createTrackbar("Max Corners", title, &maxCorners, 20, MotionDetection11CameraWindow::onChange1, this);
    createTrackbar("Quality level", title, &qualityLevel, 10000, MotionDetection11CameraWindow::onChange2, this);
    createTrackbar("Min distance", title, &minDistance, 100, MotionDetection11CameraWindow::onChange3, this);
}

void MotionDetection11CameraWindow::postprocess(Mat &image, Mat &transformed) {
//    Mat result(image.rows, image.cols * 2, image.type());
//    Util::pictureInPicture(image, transformed, 10, 10, 160, 120);
//    Util::pictureInPicture(image, result, 0, 0);
//    Util::pictureInPicture(transformed, result, image.cols, 0);
//    result.copyTo(transformed);
}

OpticalFlowMotionDetection *MotionDetection11CameraWindow::getTransformation() {
    return (OpticalFlowMotionDetection*) getT();
}

void MotionDetection11CameraWindow::onChange1(int c, void *p) {
    MotionDetection11CameraWindow *w = (MotionDetection11CameraWindow *) p;
    w->getTransformation()->maxCorners = w->maxCorners;
    w->getTransformation()->reset();
}

void MotionDetection11CameraWindow::onChange2(int c, void *p) {
    MotionDetection11CameraWindow *w = (MotionDetection11CameraWindow *) p;
    w->getTransformation()->qualityLevel = (double) (1.0 + w->qualityLevel) / 10000;
    w->getTransformation()->reset();
}

void MotionDetection11CameraWindow::onChange3(int c, void *p) {
    MotionDetection11CameraWindow *w = (MotionDetection11CameraWindow *) p;
    w->getTransformation()->minDistance = (double) 640.0 * w->minDistance / 100;
    w->getTransformation()->reset();
}