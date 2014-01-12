//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "VideoFilterWindow.h"
using namespace cv;

VideoFilterWindow::VideoFilterWindow(std::string title, std::string path, Transformation* transformation):FilterWindow(title, transformation) {
    this->path = path;
    capture = new VideoCapture(path);
}

void VideoFilterWindow::show() {
    Mat image;
    capture->read(image);
    preprocess(image);
    if (getT() == 0) {
        postprocess(image, image);
        imshow(getTitle(), image);
        image.release();
    } else {
        cv::Mat transformed = getT()->transform(image);
        postprocess(image, transformed);
        imshow(getTitle(), transformed);
        image.release();
        transformed.release();
    }
}