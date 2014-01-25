//
// Created by Kuba Sławiński on 21/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "SynchronizedVideoCapture.h"
#include "App.h"

bool SynchronizedVideoCapture::readNew = false;
SynchronizedVideoCapture* SynchronizedVideoCapture::instance = 0;

bool SynchronizedVideoCapture::read(cv::Mat &image) {
    bool result;
    if (!readNew) {
        result = true;
    } else {
        lastRead.release();
        result = VideoCapture::read(lastRead);

        cv::resize(lastRead, lastRead, cv::Size(lastRead.cols * factor, lastRead.rows * factor));
        readNew = result && !lastRead.empty();
    }
    lastRead.copyTo(image);
    return result;
}

void SynchronizedVideoCapture::refresh() {
    SynchronizedVideoCapture::readNew = true;
}

SynchronizedVideoCapture::SynchronizedVideoCapture():VideoCapture() {
    for (int i = 0; i < 1500; i++) {
        if (open(i)) {
            std::cout << "Found camera " << i << "\n";
            break;
        }
    }
    if (!isOpened())
        return;

    double width = get(CV_CAP_PROP_FRAME_WIDTH);
    double height = get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = get(CV_CAP_PROP_FPS);

    factor = 1.0;

    printf("System camera: %.0fx%.0f@%.2fFPS\n", width, height, fps);
}

SynchronizedVideoCapture* SynchronizedVideoCapture::getInstance() {
    if (instance == 0)
        instance = new SynchronizedVideoCapture();
    return instance;
}
