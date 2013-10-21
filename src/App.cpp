//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "App.h"
#include "VideoWindow.h"
#include "CameraCaptureWindow.h"
#include "SynchronizedVideoCapture.h"
#include "ManipulationWindow.h"
#include "HighestValue.h"
#include "AppConfig.h"

using namespace cv;

App::App() {
    this->done = false;
    capture = SynchronizedVideoCapture::getInstance();
}

void App::run() {
    registerWindow(new ManipulationWindow("Manipulation Window"));
    registerWindow(new FilterWindow("Highest Value", new HighestValue()));
//    registerWindow(new FilterWindow("Gray Scale", new GrayScale()));
//    registerWindow(new VideoWindow("Video", "/Users/ghaxx/a.avi"));
//    registerWindow(new CameraCaptureWindow("SynchronizedVideoCapture Capture"));

    do {
        debug("-- Loop -------------\n");
        capture->refresh();

        for(std::vector<DisplayWindow *>::iterator it = windows.begin(); it != windows.end(); ++it) {
            try {
                (*it)->show();
            } catch (Exception ignore) {}
        }
        this->catchAction();
    } while (!this->done);
}

void App::catchAction() {
    int key = waitKey(34);
    if (key == 27)
        done = true;

    for(std::vector<DisplayWindow *>::iterator it = windows.begin(); it != windows.end(); ++it) {
        (*it)->control(key);
    }
}

void App::registerWindow(DisplayWindow * window) {
    window->setApp(this);
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
