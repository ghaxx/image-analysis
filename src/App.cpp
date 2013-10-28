//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "App.h"
#include "VideoWindow.h"
#include "CameraCaptureWindow.h"
#include "SynchronizedVideoCapture.h"
#include "HighestValue.h"
#include "AppConfig.h"
#include "GrayScale.h"
#include "Lightness.h"
#include "ImageFilterWindow.h"
#include "SharpenWithGaussian.h"
#include "SharpenWithMatrix.h"
#include "VideoFilterWindow.h"
#include "CameraFilterWindow.h"
#include "TransformVideo.h"
#include "Image4.h"
#include "Camera4.h"
#include "FilterChain.h"
#include "Video4.h"

using namespace cv;

App::App() {
    this->done = false;
    capture = SynchronizedVideoCapture::getInstance();
}

void App::run() {
    // Ex. 2
//    registerWindow(new ManipulationWindow("Manipulation Window"));
//    registerWindow(new CameraFilterWindow("Original", new Lightness()));

    // Ex. 3
//    registerWindow(new CameraCaptureWindow("Video", "/Users/ghaxx/a.avi"));
//    registerWindow(new VideoWindow("Video", "/Users/ghaxx/a.avi"));

    // Ex. 4
//    FilterChain* c2 = new FilterChain(2, new Lightness(), new SharpenWithMatrix());
//    new TransformVideo(c2, AppConfig::inputDir + "/4.avi", AppConfig::outputDir + "/4-new.avi");
    registerWindow(new Camera4());
    registerWindow(new Image4());
    registerWindow(new Video4());

    if (windows.size() > 0)
        do {
            capture->refresh();

            for (std::vector<DisplayWindow *>::iterator it = windows.begin(); it != windows.end(); ++it) {
                try {
                    (*it)->show();
                } catch (Exception ignore) {}
            }
            this->catchAction();
        } while (!this->done);

    for (std::vector<DisplayWindow *>::iterator it = windows.begin(); it != windows.end(); ++it) {
        delete *it;
    }
}

void App::catchAction() {
    int key = waitKey(34);
    if (key == 27)
        done = true;

    for (std::vector<DisplayWindow *>::iterator it = windows.begin(); it != windows.end(); ++it) {
        (*it)->control(key);
    }
}

void App::registerWindow(DisplayWindow *window) {
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
