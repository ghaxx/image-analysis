//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "HaarFaceWindow.h"
#include "Ex9Window.h"

using namespace cv;

HaarFaceWindow::HaarFaceWindow(const std::string &title):CameraFilterWindow(title, new HaarFaceTransformation()) {
    scaleFactor = (int) ((getTransformation()->scaleFactor - 1) * 10);
    minNeighbors = getTransformation()->minNeighbors;
    minSize = getTransformation()->minSize.width;

    createTrackbar("Scale factor", title, &scaleFactor, 10, HaarFaceWindow::onChange1, this);
    createTrackbar("Min neighbors", title, &minNeighbors, 10, HaarFaceWindow::onChange2, this);
    createTrackbar("Min size", title, &minSize, 100, HaarFaceWindow::onChange3, this);
}

HaarFaceTransformation *HaarFaceWindow::getTransformation() {
    return (HaarFaceTransformation *) getT();
}


void HaarFaceWindow::onChange1(int c, void *p) {
    HaarFaceWindow *w = (HaarFaceWindow *) p;
    w->getTransformation()->scaleFactor = 1.0 + (double) (w->scaleFactor + 1) / 10;
}

void HaarFaceWindow::onChange2(int c, void *p) {
    HaarFaceWindow *w = (HaarFaceWindow *) p;
    w->getTransformation()->minNeighbors = w->minNeighbors;
}

void HaarFaceWindow::onChange3(int c, void *p) {
    HaarFaceWindow *w = (HaarFaceWindow *) p;
    if (w->minSize == 0)
        w->getTransformation()->minSize = Size();
    else
        w->getTransformation()->minSize = Size((double) 640 * w->minSize / 100, (double) 640 * w->minSize / 100);
}