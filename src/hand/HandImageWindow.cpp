//
// Created by Kuba Sławiński on 26/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "HandImageWindow.h"
#include "FindHand.h"
#include "AppConfig.h"

HandImageWindow::HandImageWindow(const std::string &title):ImageFilterWindow(title, AppConfig::inputDir + "/h00.jpg", new FindHand()) {
    ((FindHand *) getT())->createControls(title);
    int counter = 0;
}

void HandImageWindow::control(char key) {
    if (key == 't') ((FindHand *) getT())->approxPolyEpsilon += 1;
    if (key == 'g') ((FindHand *) getT())->approxPolyEpsilon -= 1;

    if (key == 'q') counter = ++counter % 12;
    if (key == 'a') counter = (--counter + 12) % 12;

    if (key == 'a' || key == 'q') {
        char newName[50];
        sprintf(newName, "%s/h%02d.jpg", AppConfig::inputDir.c_str(), counter);
        imageFile = std::string(newName);
    }
    DisplayWindow::control(key);

    refresh();
}
