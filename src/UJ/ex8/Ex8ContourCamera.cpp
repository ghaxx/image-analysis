//
// Created by Kuba Sławiński on 06/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Ex8ContourCamera.h"
#include "Util.h"

using namespace cv;


Ex8ContourCamera::Ex8ContourCamera(const std::string &title):Ex8Generic(title) {
    capture = SynchronizedVideoCapture::getInstance();

//    refreshBackground();
}

void Ex8ContourCamera::control(char key) {
    if (key == 'x') {
        refreshBackground();
    }
}

void Ex8ContourCamera::refreshBackground() {
    capture->read(background);
    flip(background, background, 2);
    cvtColor(background, background, CV_RGB2GRAY);
    background.convertTo(accumulated, CV_32F);
}
