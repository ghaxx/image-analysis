//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include "HaarFaceTransformation.h"
#include "AppConfig.h"

using namespace cv;

cv::Mat HaarFaceTransformation::transform(Mat image) {
    Mat result;
    image.copyTo(result);
    cvtColor(result, result, CV_RGB2GRAY);

    vector<Rect> objects;
    classifier->detectMultiScale(result, objects);

    for(std::vector<Rect>::iterator it = objects.begin(); it != objects.end(); ++it) {
        circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, Scalar(0, 0, 0), 2);
        circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, Scalar(255, 255, 0), 1);
    }
    result.release();
    return image;
}

HaarFaceTransformation::HaarFaceTransformation() {
    classifier = new CascadeClassifier(AppConfig::dataDir + "/haarcascade_frontalface_default.xml");
}