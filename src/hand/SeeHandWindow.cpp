//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SeeHandWindow.h"
#include "AppConfig.h"

using namespace cv;

SeeHandWindow::SeeHandWindow(const std::string &title):CameraFilterWindow(title, new FindHand()) {
    getTransformation()->createControls(title);
}

FindHand *SeeHandWindow::getTransformation() {
    return (FindHand*) getT();
}


void SeeHandWindow::control(char key) {
    if (key == 'w') getTransformation()->setMinHue(getTransformation()->minHue + 1);
    if (key == 's') getTransformation()->setMinHue(getTransformation()->minHue - 1);

    if (key == 'e') getTransformation()->setMaxHue(getTransformation()->maxHue + 1);
    if (key == 'd') getTransformation()->setMaxHue(getTransformation()->maxHue - 1);

    if (key == 'r') getTransformation()->setBlurRadius(getTransformation()->blurRadius + 1);
    if (key == 'f') getTransformation()->setBlurRadius(getTransformation()->blurRadius - 1);

//    if (key != '\xff')
//        printf("Hue: %d - %d, Blur: %d, Morph: %s\r", minHue, maxHue, blurRadius, morph ? "yes" : "no");
    CameraFilterWindow::control(key);
}