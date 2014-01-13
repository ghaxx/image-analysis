//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraFilterWindow.h"
#include "AppConfig.h"

using namespace cv;

CameraFilterWindow::CameraFilterWindow(std::string title, Transformation *transformation):FilterWindow(title, transformation) {
    capture = SynchronizedVideoCapture::getInstance();
    writer = new VideoWriter();
    record = false;
}

void CameraFilterWindow::show() {
    Mat image;
    capture->read(image);
    if (image.empty())
        return;

    flip(image, image, 2);
    preprocess(image);
    if (getT() == 0) {
        postprocess(image, image);
        imshow(getTitle(), image);
        if (record && writer->isOpened()) {
            writer->write(image);
        }
        image.release();
    } else {
        cv::Mat transformed = getT()->transform(image);
        postprocess(image, transformed);
        imshow(getTitle(), transformed);
        if (record && writer->isOpened()) {
            writer->write(transformed);
        }
        image.release();
        transformed.release();
    }
}

void CameraFilterWindow::control(char key) {
    if (key == ' ') {
        record = !record;
        if (record) {
            char name[100];
            sprintf(name, (AppConfig::outputDir + "/camera %li.avi").c_str(), time(0));
            printf("Recording started and will be saved as %s\n", name);
            writer->open(name, 0, 15.0, Size(640, 480), true);
        } else {
            printf("Recording ended\n");
            writer->release();
        }
    }
    FilterWindow::control(key);
}
