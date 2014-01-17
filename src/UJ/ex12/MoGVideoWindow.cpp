//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MoGVideoWindow.h"

MoGVideoWindow::MoGVideoWindow(const std::string &title, const std::string &path):VideoFilterWindow(title, path, new MoGMotionDetection()) {
    getTransformation()->createControls(title);
}

MoGMotionDetection *MoGVideoWindow::getTransformation() {
    return (MoGMotionDetection*) getT();
}
