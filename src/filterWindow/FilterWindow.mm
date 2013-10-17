//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "FilterWindow.h"

FilterWindow::FilterWindow(const std::string title, Transformation *t):ImageWindow(title) {
    this->t = t;
}

FilterWindow::~FilterWindow() {
    delete t;
}

void FilterWindow::show(cv::Mat mat) {
    App::debug("Filter\n");
    ImageWindow::show(t->transform(mat));
}

Transformation* FilterWindow::getT() const {
    return t;
}

