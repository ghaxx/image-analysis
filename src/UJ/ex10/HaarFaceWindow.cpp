//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "HaarFaceWindow.h"
#include "Ex9Window.h"

using namespace cv;

HaarFaceWindow::HaarFaceWindow(const std::string &title):CameraFilterWindow(title, new HaarFaceTransformation()) {
    getTransformation()->createControls(title);
}

HaarFaceTransformation *HaarFaceWindow::getTransformation() {
    return (HaarFaceTransformation *) getT();
}
