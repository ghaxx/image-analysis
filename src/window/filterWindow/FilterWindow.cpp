//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#import "FilterWindow.h"
#import "App.h"


FilterWindow::FilterWindow(const std::string title, Transformation *t):DisplayWindow(title) {
    this->t = t;
    capture = SynchronizedVideoCapture::getInstance();
}

FilterWindow::~FilterWindow() {
    delete t;
}

void FilterWindow::show() {
    cv::Mat mat;
    capture->read(mat);
    App::debug("Filter\n");
    imshow(getTitle().c_str(), t->transform(mat));
}

Transformation* FilterWindow::getT() const {
    return t;
}

