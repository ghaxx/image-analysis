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

    for (int i = 0; i < 2; i++) {
        CascadeClassifier *classifier = classifiers[i];
        vector<Rect> objects;
        classifier->detectMultiScale(result, objects, scaleFactor, minNeighbors, 0, minSize);

        for(std::vector<Rect>::iterator it = objects.begin(); it != objects.end(); ++it) {
            circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, Scalar(0, 0, 0), 2);
            circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, Scalar(i%3 ? 0 : 255, (i+1)%3 ? 0 : 255, (i+2)%3 ? 0 : 255), 1);
        }
    }
    result.release();
    return image;
}

HaarFaceTransformation::HaarFaceTransformation() {
    classifiers = new CascadeClassifier*[3];
    classifiers[3] = new CascadeClassifier(AppConfig::dataDir + "/haarcascade_frontalface_default.xml");
    classifiers[0] = new CascadeClassifier(AppConfig::dataDir + "/fist.xml");
    classifiers[1] = new CascadeClassifier(AppConfig::dataDir + "/palm.xml");
    scaleFactor = 1.1;
    minNeighbors = 3;
    minSize = Size();
}