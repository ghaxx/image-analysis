//
// Created by Kuba Sławiński on 18/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "CameraCaptureWindow.h"
#include "AppConfig.h"

using namespace cv;

CameraCaptureWindow::CameraCaptureWindow(std::string title):DisplayWindow(title) {
    capture = SynchronizedVideoCapture::getInstance();
    captureFrame = false;
    start = clock();

    if (AppConfig::argc > 1) {
        timeout = atof(AppConfig::argv[1]);
        printf ("Timeout: %f\n", timeout);
    } else {
        timeout = 5000000;
    }
}

void CameraCaptureWindow::show() {
    cv::Mat image;
    capture->read(image);
    double milliseconds = 1000.0 * (clock() - start) / CLOCKS_PER_SEC;
    if (captureFrame || milliseconds > timeout) {
        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(80);

        char name[100];
        sprintf(name, strcat(AppConfig::outputDir, "capture_%d.jpg"), time(0));
        imwrite(name, image, params);
        cv::putText(image, "Saving...", cvPoint(10,30), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);
        captureFrame = false;
    } else if (milliseconds <= timeout) {
        char elapsed[100];
        sprintf(elapsed, "Captureing in: %.0f", (timeout - milliseconds) / 1000);
        cv::putText(image, elapsed, cvPoint(10,30), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);
    }

    imshow(getTitle().c_str(), image);
    image.release();
}

void CameraCaptureWindow::control(char key) {
    if (key == 'c')
        captureFrame = true;
}
