//
// Created by Kuba Sławiński on 13/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Ex9Window.h"
#include "FindLines.h"

using namespace cv;

Ex9Window::Ex9Window(const std::string &title):CameraFilterWindow(title, new FindLines()) {
    capture = SynchronizedVideoCapture::getInstance();

    rho = 1;
    theta = 1;
    thresh = 50;
    minLineLength = 5;
    maxLineGap = 10;

    createTrackbar("Threshold", title, &thresh, 100, onThreshChange, this);
    createTrackbar("Rho", title, &rho, 100, onChange1, this);
    createTrackbar("Theta", title, &theta, 100, Ex9Window::onChange2, this);
    createTrackbar("Max gap", title, &maxLineGap, 100, Ex9Window::onChange3, this);
    createTrackbar("Min length", title, &minLineLength, 100, Ex9Window::onChange4, this);
}

FindLines *Ex9Window::getFilter() {
    return (FindLines *) getT();
}

void Ex9Window::onThreshChange(int c, void *p) {
    Ex9Window *w = (Ex9Window *) p;
    w->getFilter()->thresh = w->thresh;
}

void Ex9Window::onChange1(int c, void *p) {
    Ex9Window *w = (Ex9Window *) p;
    w->getFilter()->rho = w->rho;
}

void Ex9Window::onChange2(int c, void *p) {
    Ex9Window *w = (Ex9Window *) p;
    w->getFilter()->theta = (double) w->theta * CV_PI / 180;
}

void Ex9Window::onChange3(int c, void *p) {
    Ex9Window *w = (Ex9Window *) p;
    w->getFilter()->maxLineGap = w->maxLineGap;
}

void Ex9Window::onChange4(int c, void *p) {
    Ex9Window *w = (Ex9Window *) p;
    w->getFilter()->minLineLength = w->minLineLength;
}