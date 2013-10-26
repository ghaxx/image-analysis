//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraFilterWindow.h"

using namespace cv;

CameraFilterWindow::CameraFilterWindow(const char* title, std::vector<Transformation *> *transformations):FilterWindow(title, transformations) {
    init();
}

CameraFilterWindow::CameraFilterWindow(const char* title, Transformation *transformation):FilterWindow(title, transformation) {
    init();
}

void CameraFilterWindow::init() {
    capture = SynchronizedVideoCapture::getInstance();
    printf("Opening video writer\n");
    writer = new VideoWriter();
    writer->open("/Users/ghaxx/camera.avi", 0, 30.0, Size(640, 480), true);
}

void CameraFilterWindow::show() {
    Mat image;
    capture->read(image);
    App::debug(getTitle());
    if (getT() == 0) {
        imshow(getTitle(), image);
        image.release();
    } else {
        cv::Mat transformed(image);

        for (std::vector<Transformation *>::iterator it = getT()->begin(); it != getT()->end(); ++it) {
            transformed = (*it)->transform(transformed);
        }

        cv::resize(transformed, transformed, cv::Size(640, 480));
        writer->write(transformed);
        imshow(getTitle(), transformed);
        image.release();
        transformed.release();
    }
}

CameraFilterWindow::~CameraFilterWindow() {
    printf("Releasing video writer\n");
    writer->release();
    delete writer;
}
