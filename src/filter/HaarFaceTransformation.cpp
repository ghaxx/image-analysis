//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include <opencv2/highgui/highgui.hpp>
#include "HaarFaceTransformation.h"
#include "AppConfig.h"

using namespace cv;

cv::Mat HaarFaceTransformation::transform(Mat image) {
    Mat result;
    image.copyTo(result);
    cvtColor(result, result, CV_RGB2GRAY);
    Size s;

    for (int i = 0; i < 2; i++) {
        CascadeClassifier *classifier = classifiers[i];
        vector<Rect> objects;
        classifier->detectMultiScale(result, objects, scaleFactor, minNeighbors, 0, minSize);

        for(std::vector<Rect>::iterator it = objects.begin(); it != objects.end(); ++it) {
            Scalar_<double> color = Scalar(i%3 ? 200 : 255, (i+1)%3 ? 200 : 255, (i+2)%3 ? 200 : 255);
            int baseLine;

            circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, Scalar(0, 0, 0), 2);
            circle(image, Point(it->x + it->width/2, it->y + it->height/2), it->height/2, color, 1);
            s = getTextSize(items[i], cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, 2, &baseLine);
            putText(image, items[i], Point(it->x + it->width/2 - s.width / 2, it->y - 3), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, Scalar(0, 0, 0), 2, CV_AA);
//            s = getTextSize(items[i], cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, 1, &baseLine);
            putText(image, items[i], Point(it->x + it->width/2 - s.width / 2, it->y - 3), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, color, 1, CV_AA);
        }
    }
    result.release();
    return image;
}

HaarFaceTransformation::HaarFaceTransformation() {
    classifiers = new CascadeClassifier*[3];
    items = new std::string[3];
    classifiers[0] = new CascadeClassifier(AppConfig::dataDir + "/haarcascade_frontalface_default.xml");
    items[0] = "Face";
    classifiers[1] = new CascadeClassifier(AppConfig::dataDir + "/fist.xml");
    items[1] = "Fist";
    classifiers[2] = new CascadeClassifier(AppConfig::dataDir + "/palm.xml");
    items[2] = "Palm";
    scaleFactor = 1.1;
    minNeighbors = 3;
    minSize = Size();

    _scaleFactor = (int) ((scaleFactor - 1) * 10);
    _minSize = minSize.width;
}

void HaarFaceTransformation::createControls(std::string windowTitle) {
    string suffix = " - controls";
    namedWindow(windowTitle + suffix);
    imshow(windowTitle + suffix, Mat::zeros(1, 500, CV_8UC1));

    createTrackbar("Scale factor", windowTitle + suffix, &_scaleFactor, 10, HaarFaceTransformation::onChange1, this);
    createTrackbar("Min neighbors", windowTitle + suffix, &minNeighbors, 10);
    createTrackbar("Min size", windowTitle + suffix, &_minSize, 100, HaarFaceTransformation::onChange3, this);
}


void HaarFaceTransformation::onChange1(int c, void *p) {
    HaarFaceTransformation *w = (HaarFaceTransformation *) p;
    w->scaleFactor = 1.0 + (double) (w->scaleFactor + 1) / 10;
}

void HaarFaceTransformation::onChange3(int c, void *p) {
    HaarFaceTransformation *w = (HaarFaceTransformation *) p;
    if (w->_minSize == 0)
        w->minSize = Size();
    else
        w->minSize = Size((double) 640 * w->_minSize / 100, (double) 640 * w->_minSize / 100);
}