//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "DisplayWindow.h"
#include "App.h"

using namespace cv;

DisplayWindow::DisplayWindow(string title) {
    this->title = title;
    namedWindow(title, CV_WINDOW_AUTOSIZE);
}

void DisplayWindow::control(char key) {

}

App *DisplayWindow::getApp() const {
    return app;
}

void DisplayWindow::setApp(App *app) {
    DisplayWindow::app = app;
}

std::string DisplayWindow::getTitle() const {
    return title;
}

DisplayWindow::~DisplayWindow() {
    printf("Deleting window\n");
}