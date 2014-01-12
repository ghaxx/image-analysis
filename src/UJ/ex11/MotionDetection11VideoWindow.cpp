//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MotionDetection11VideoWindow.h"

using namespace cv;

MotionDetection11VideoWindow::MotionDetection11VideoWindow(const std::string &title, const std::string &path):VideoFilterWindow(title, path, new OpticalFlowMotionDetection()) {
    maxCorners = getTransformation()->maxCorners;
       qualityLevel = (int) (getTransformation()->qualityLevel * 10000 - 1);
       minDistance = (int) getTransformation()->minDistance;
       
       createTrackbar("Max Corners", title, &maxCorners, 20, MotionDetection11VideoWindow::onChange1, this);
       createTrackbar("Quality level", title, &qualityLevel, 10000, MotionDetection11VideoWindow::onChange2, this);
       createTrackbar("Min distance", title, &minDistance, 100, MotionDetection11VideoWindow::onChange3, this);
}


OpticalFlowMotionDetection *MotionDetection11VideoWindow::getTransformation() {
    return (OpticalFlowMotionDetection*) getT();
}

void MotionDetection11VideoWindow::onChange1(int c, void *p) {
    MotionDetection11VideoWindow *w = (MotionDetection11VideoWindow *) p;
    w->getTransformation()->maxCorners = w->maxCorners;
    w->getTransformation()->reset();
}

void MotionDetection11VideoWindow::onChange2(int c, void *p) {
    MotionDetection11VideoWindow *w = (MotionDetection11VideoWindow *) p;
    w->getTransformation()->qualityLevel = (double) (1.0 + w->qualityLevel) / 10000;
    w->getTransformation()->reset();
}

void MotionDetection11VideoWindow::onChange3(int c, void *p) {
    MotionDetection11VideoWindow *w = (MotionDetection11VideoWindow *) p;
    w->getTransformation()->minDistance = (double) 640.0 * w->minDistance / 100;
    w->getTransformation()->reset();
}