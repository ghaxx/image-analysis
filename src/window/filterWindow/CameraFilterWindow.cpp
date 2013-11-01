//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraFilterWindow.h"

using namespace cv;

CameraFilterWindow::CameraFilterWindow(std::string title, Transformation* transformation):FilterWindow(title, transformation) {
    capture = SynchronizedVideoCapture::getInstance();
}

void CameraFilterWindow::show() {
    Mat image;
    capture->read(image);
    preprocess(image);
    if (getT() == 0) {
        postprocess(image);
        imshow(getTitle(), image);
        image.release();
    } else {
        cv::Mat transformed = getT()->transform(image);
        postprocess(transformed);
        imshow(getTitle(), transformed);
        image.release();
        transformed.release();
    }
}
