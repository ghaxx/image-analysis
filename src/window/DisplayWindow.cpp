//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "DisplayWindow.h"
#include "App.h"

using namespace cv;

ImageWindow::ImageWindow(std::string title) {
    this->title = title;
    namedWindow(title.c_str(), CV_WINDOW_AUTOSIZE);
}

void ImageWindow::control(char key) {

}

App *ImageWindow::getApp() const {
    return app;
}

void ImageWindow::setApp(App *app) {
    ImageWindow::app = app;
}

const std::string &ImageWindow::getTitle() const {
    return title;
}