//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#import "FilterWindow.h"
#import "App.h"



FilterWindow::~FilterWindow() {
    delete t;
}

Transformation* FilterWindow::getT() const {
    return t;
}

FilterWindow::FilterWindow(std::string title, Transformation* transformation):DisplayWindow(title) {
    this->t = transformation;
}

void FilterWindow::preprocess(cv::Mat &image) {

}

void FilterWindow::postprocess(cv::Mat &image, cv::Mat &transformed) {

}
