//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraFilterWindow.h"

using namespace cv;

CameraFilterWindow::CameraFilterWindow(const char* title, Transformation* transformation):FilterWindow(title, transformation) {
    capture = SynchronizedVideoCapture::getInstance();
    printf("Opening video writer\n");
    writer = new VideoWriter();
}

void CameraFilterWindow::show() {
    Mat image;
    capture->read(image);
    preprocess(image);
    App::debug(getTitle());
    if (getT() == 0) {
        if (record && writer->isOpened())
            writer->write(image);
        postprocess(image);
        imshow(getTitle(), image);
        image.release();
    } else {
        cv::Mat transformed = getT()->transform(image);
        cv::resize(transformed, transformed, cv::Size(640, 480));
        if (record)
            writer->write(transformed);
        postprocess(transformed);
        imshow(getTitle(), transformed);
        image.release();
        transformed.release();
    }
}

CameraFilterWindow::~CameraFilterWindow() {
    printf("Releasing video writer\n");
    if (writer->isOpened())
        writer->release();
    delete writer;
}
