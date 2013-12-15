//
// Created by Kuba Sławiński on 06/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Ex8Generic.h"
#include "Util.h"

using namespace cv;

void Ex8Generic::show() {
    Mat cameraImage;
    Mat cameraImageGray;
    Mat difference;
    Mat accumulated8U;
    capture->read(cameraImage);
    if (cameraImage.empty())
        return;
    flip(cameraImage, cameraImage, 2);
    Mat result = Mat::zeros(240, 640, cameraImage.type());

    cvtColor(cameraImage, cameraImageGray, CV_RGB2GRAY);

    if (accumulated.empty())
        cameraImageGray.convertTo(accumulated, CV_32F);

    try {
        accumulated.convertTo(accumulated8U, CV_8U);
        try {
            absdiff(accumulated8U, cameraImageGray, difference);
            try {
                threshold(difference, difference, thresh, 255, cv::THRESH_BINARY);
                try {
                    accumulateWeighted(cameraImageGray, accumulated, (double) learningRate / 1000);

                    Mat accumulatedAbs;
                    try {
                        convertScaleAbs(accumulated, accumulatedAbs);
                        Util::pictureInPicture(accumulatedAbs, result, 0, 0, 320, 240);
                        Util::pictureInPicture(difference, result, 320, 0, 320, 240);
                        imshow(getTitle(), result);
                    } catch(...) {
                        printf("convertScaleAbs\n");
                    }


                } catch(...) {
                    printf("accumulate\n");
                }
            } catch(...) {
                printf("threshold\n");
            }
        } catch(...) {
            printf("absdiff\n");
        }
    } catch(...) {
        printf("convertTo\n");
    }

    difference.release();

    cameraImage.release();

    cameraImageGray.release();
}

Ex8Generic::Ex8Generic(const std::string &title):DisplayWindow(title) {
    learningRate = 70;
    thresh = 30;
//    background = Mat::zeros(480, 640, CV_8UC1);
//    cvtColor(background, background, CV_RGB2GRAY);
    createTrackbar("Learning rate * 1000", title, &learningRate, 1000);
    createTrackbar("Threshold", title, &thresh, 100);
}
