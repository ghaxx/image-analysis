//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MotionDetection11VideoWindow.h"

using namespace cv;

MotionDetection11VideoWindow::MotionDetection11VideoWindow(const std::string &title, const std::string &path):VideoFilterWindow(title, path, new OpticalFlowMotionDetection()) {
    getTransformation()->createControls(title);
}


OpticalFlowMotionDetection *MotionDetection11VideoWindow::getTransformation() {
    return (OpticalFlowMotionDetection*) getT();
}