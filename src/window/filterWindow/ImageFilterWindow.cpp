//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "ImageFilterWindow.h"

using namespace cv;

ImageFilterWindow::ImageFilterWindow(std::string title, std::string imageFile, Transformation* transformation):FilterWindow(title, transformation) {
    this->imageFile = imageFile;
    image = imread(imageFile, CV_LOAD_IMAGE_COLOR);
    _refresh = TRUE;
}

void ImageFilterWindow::show() {
    if (_refresh) {
        _refresh = 0;
        preprocess(image);
        if (getT() == 0) {
            postprocess(image, image);
            imshow(getTitle(), image);
        } else {
            cv::Mat transformed = getT()->transform(image);
            postprocess(image, transformed);
            imshow(getTitle(), transformed);
            transformed.release();
        }
    }
}

void ImageFilterWindow::refresh() {
    _refresh = TRUE;
}

cv::Mat const &ImageFilterWindow::getImage() const {
    return image;
}