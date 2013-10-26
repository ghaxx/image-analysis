//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "ImageFilterWindow.h"

using namespace cv;

ImageFilterWindow::ImageFilterWindow(const char* title, const char *imageFile, std::vector<Transformation *> *transformations):FilterWindow(title, transformations) {
    this->imageFile = imageFile;
    image = imread(imageFile, CV_LOAD_IMAGE_COLOR);
    _refresh = TRUE;
}

void ImageFilterWindow::show() {
    if (_refresh) {
        _refresh = 0;
        App::debug(getTitle());
        if (getT() == 0) {
            imshow(getTitle(), image);
        } else {
            cv::Mat transformed(image);

            for (std::vector<Transformation *>::iterator it = getT()->begin(); it != getT()->end(); ++it) {
                transformed = (*it)->transform(transformed);
            }
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