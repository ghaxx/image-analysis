//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "App.h"
#import "ManipulationWindow.h"
#include "HighestValue.h"
#include "GrayScale.h"

using namespace cv;

App::App() {
    this->done = false;
}

void App::run() {
    Mat image;
    VideoCapture cap;
    for (int i = 0; i < 1500; i++) {
        if (cap.open(i)) {
            std::cout << "Found camera " << i << "\n";
            break;
        }
    }
    if (!cap.isOpened())
        return;

    registerWindow(new ManipulationWindow("Manipulation Window"));
    registerWindow(new FilterWindow("Highest Value", new HighestValue()));
    registerWindow(new FilterWindow("Gray Scale", new GrayScale()));

    do {
        debug("-- Loop -------------\n");
        try {
            cap >> image;
            for(std::vector<ImageWindow*>::iterator it = windows.begin(); it != windows.end(); ++it) {
                (*it)->show(image);
            }
        } catch (Exception ignore) {}
        this->catchAction();
    } while (!this->done);
}

void App::catchAction() {
    int key = waitKey(34);
    if (key == 27)
        done = true;

    for(std::vector<ImageWindow*>::iterator it = windows.begin(); it != windows.end(); ++it) {
        (*it)->control(key);
    }
}

void App::registerWindow(ImageWindow* window) {
    windows.push_back(window);
}


void App::debug(const char *format, ...) {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCSimplifyInspection"
#pragma clang diagnostic ignored "-Wunreachable-code"
    if (App::logLevel <= 1) {
        va_list args;
        va_start(args, format);
        printf(format, args);
    }
#pragma clang diagnostic pop
}
