//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MoGMotionDetectionCameraWindow.h"
#include "OpticalFlowMotionDetection.h"

MoGMotionDetectionCameraWindow::MoGMotionDetectionCameraWindow(const std::string &title):CameraFilterWindow(title, new MoGMotionDetection()) {
    getTransformation()->createControls(title);
}

MoGMotionDetection *MoGMotionDetectionCameraWindow::getTransformation() {
    return (MoGMotionDetection*) getT();
}
