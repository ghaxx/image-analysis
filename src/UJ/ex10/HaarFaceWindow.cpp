//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "HaarFaceWindow.h"

HaarFaceWindow::HaarFaceWindow(const std::string &title):CameraFilterWindow(title, new HaarFaceTransformation()) {
}

HaarFaceTransformation* HaarFaceWindow::getTransformation() {
    return (HaarFaceTransformation*) getT();
}
