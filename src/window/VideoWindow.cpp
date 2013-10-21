//
// Created by Kuba Sławiński on 18/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "VideoWindow.h"
#include "AppConfig.h"

using namespace cv;

VideoWindow::VideoWindow(const std::string &title, const char* path):DisplayWindow(title) {
    capture = new VideoCapture(path);
    frameNumber = 0;
}

void VideoWindow::show() {
    Mat image;
    capture->read(image);

    double width = capture->get(CV_CAP_PROP_FRAME_WIDTH);
    double height = capture->get(CV_CAP_PROP_FRAME_HEIGHT);
    double fps = capture->get(CV_CAP_PROP_FPS);


    if ((double) frameNumber * (1000/fps) > 3000) {
        vector<int> params;
        params.push_back(CV_IMWRITE_JPEG_QUALITY);
        params.push_back(80);

        char name[100];

        sprintf(name, "%s/image_%04d.jpg", AppConfig::outputDir, frameNumber);
        imwrite(name, image, params);
        cv::putText(image, "Saving...", cvPoint(10,30), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);
    }

    char a[100];
    sprintf(a, "%.0fx%.0f@%.2fFPS", width, height, fps);
    cv::putText(image, a, cvPoint(10,15), cv::FONT_HERSHEY_PLAIN, 1, cvScalar(120,120,250), 1, CV_AA);

    imshow(getTitle().c_str(), image);
    frameNumber++;
}

VideoWindow::~VideoWindow() {
    delete capture;
}