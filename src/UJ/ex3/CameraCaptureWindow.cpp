//
// Created by Kuba Sławiński on 18/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraCaptureWindow.h"
#include "AppConfig.h"

using namespace boost;
using namespace cv;

CameraCaptureWindow::CameraCaptureWindow(std::string title):DisplayWindow(title) {
    capture = SynchronizedVideoCapture::getInstance();
    captureFrame = false;
    timer = new progress_timer();

    if (AppConfig::argc > 1) {
        timeout = atof(AppConfig::argv[1]);
        printf ("Timeout: %f\n", timeout);
    } else {
        timeout = 5;
    }
}

void CameraCaptureWindow::show() {
    cv::Mat image;
    capture->read(image);
    double elapsed = timer->elapsed();
    if (captureFrame || elapsed > timeout) {
        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(80);

        char name[100];
        sprintf(name, "%s/capture_%li.jpg", AppConfig::outputDir.c_str(), time(0));
        imwrite(name, image, params);
        cv::putText(image, "Saving...", cvPoint(10,30), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);
        captureFrame = false;
    } else if (elapsed <= timeout) {
        char msg[100];
        sprintf(msg, "Captureing in: %.0f", timeout - elapsed);
        cv::putText(image, msg, cvPoint(10,30), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);
    }
    imshow(getTitle(), image);
    image.release();
}

void CameraCaptureWindow::control(char key) {
    if (key == 'c')
        captureFrame = true;
}
