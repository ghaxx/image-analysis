//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "MotionDetection11CameraWindow.h"
#include "Util.h"
#include "OpticalFlowMotionDetection.h"

using namespace cv;

MotionDetection11CameraWindow::MotionDetection11CameraWindow(const std::string &title):CameraFilterWindow(title, new OpticalFlowMotionDetection()) {
    getTransformation()->createControls(title);
}

void MotionDetection11CameraWindow::postprocess(Mat &image, Mat &transformed) {
//    Mat result(image.rows, image.cols * 2, image.type());
//    Util::pictureInPicture(image, transformed, 10, 10, 160, 120);
//    Util::pictureInPicture(image, result, 0, 0);
//    Util::pictureInPicture(transformed, result, image.cols, 0);
//    result.copyTo(transformed);
}

OpticalFlowMotionDetection *MotionDetection11CameraWindow::getTransformation() {
    return (OpticalFlowMotionDetection*) getT();
}
