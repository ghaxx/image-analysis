//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "ImageWindow.h"

using namespace cv;

ImageWindow::ImageWindow(std::string title) {
    this->title = title;
    namedWindow(title.c_str(), CV_WINDOW_AUTOSIZE);
}

void ImageWindow::show(cv::Mat mat) {
    imshow(title.c_str(), mat);
}