//
// Created by Kuba Sławiński on 21/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SynchronizedVideoCapture.h"
#include "App.h"

bool SynchronizedVideoCapture::readNew = false;

bool SynchronizedVideoCapture::read(cv::Mat &image) {
    bool result;
    if (!readNew) {
        App::debug("Getting from buffer\n");
        result = true;
    } else {
        App::debug("Getting new image from camera\n");
        readNew = false;
        result = VideoCapture::read(lastRead);
    }
    lastRead.copyTo(image);
    return result;
}

void SynchronizedVideoCapture::refresh() {
    SynchronizedVideoCapture::readNew = true;
}

SynchronizedVideoCapture::SynchronizedVideoCapture():VideoCapture() {
}