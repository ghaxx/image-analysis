//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "VideoFilterWindow.h"
using namespace cv;

VideoFilterWindow::VideoFilterWindow(const char* title, const char *path, Transformation* transformation):FilterWindow(title, transformation) {
    capture = new VideoCapture(path);
}

void VideoFilterWindow::show() {
    Mat image;
    capture->read(image);
    App::debug(getTitle());
    if (getT() == 0) {
        imshow(getTitle(), image);
        image.release();
    } else {
        cv::Mat transformed = getT()->transform(image);
        imshow(getTitle(), transformed);
        image.release();
        transformed.release();
    }
}