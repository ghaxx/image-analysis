//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//


#include <opencv2/highgui/highgui.hpp>
#include "OpticalFlowMotionDetection.h"
#include "Util.h"

using namespace std;
using namespace cv;


OpticalFlowMotionDetection::OpticalFlowMotionDetection() {
    maxCorners = 50;
    qualityLevel = 0.0001;
    minDistance = 1;
    found = 0;
    trailSize = 15;

    _qualityLevel = (int) qualityLevel * 10000 - 1;
    _minDistance = (int) minDistance;
}

cv::Mat OpticalFlowMotionDetection::transform(Mat image) {
    flip(image, image, 2);
    int foundNow = 0;
    Mat dots = Mat::zeros(image.rows, image.cols, image.type());
    if (image_next.empty() || features_next.size() == 0) {
        cvtColor(image, image_next, CV_RGB2GRAY);
        goodFeaturesToTrack(
                image_next,
                features_next,
                maxCorners,
                qualityLevel,
                minDistance
        );
        features_first = features_next;
    } else {
        cvtColor(image, image_next, CV_RGB2GRAY);
        features_next.clear();
        calcOpticalFlowPyrLK(
                image_prev, image_next,
                features_prev,
                features_next,
                status,
                err
        );
        Mat currentLines = Mat::zeros(image.rows, image.cols, image.type());
        for (int i = 0; i < status.size(); i++) {
            Point2i pt0 = Point(features_first[i].x, features_first[i].y);
            Point2i pt2 = Point(features_next[i].x, features_next[i].y);
            Point2i pt1 = Point(features_prev[i].x, features_prev[i].y);
            if ((int) status[i] == 1 && Util::quickDistance(pt2, pt1) > 2) {
                foundNow++;
                line(currentLines, pt1, pt2, Scalar(0, 0, 0), 2);
                circle(dots, pt2, 2, Scalar(0, 0, 0), -1);

                line(currentLines, pt1, pt2, Scalar(255, 255, 255), 1);
                circle(dots, pt2, 1, Scalar(255, 255, 255), -1);
            }
        }
        lines.push_back(currentLines);
        if (lines.size() > trailSize)
            lines.pop_front();

        if (foundNow < (float) found / 2 || foundNow == 0) {
            reset();
        }
    }
    double i = 1;
    for (std::list<Mat>::iterator it = lines.begin(); it != lines.end(); ++it) {
        Util::addAlphaMat(*it, image, i++ / trailSize);
    }
    Util::addAlphaMat(dots, image, 1.0);
    dots.release();
    image_prev = image_next.clone();
    features_prev = features_next;
    found = foundNow;
    return image;
}

void OpticalFlowMotionDetection::reset() {
    image_prev.release();

    features_prev.clear();
    features_next.clear();

    found = 0;
}

void OpticalFlowMotionDetection::createControls(const std::string &windowTitle) {
    string suffix = " - controls";
    namedWindow(windowTitle + suffix);
    imshow(windowTitle + suffix, Mat::zeros(1, 500, CV_8UC1));
    createTrackbar("Max Corners", windowTitle + suffix, &maxCorners, 400, OpticalFlowMotionDetection::onChange1, this);
    createTrackbar("Quality level", windowTitle + suffix, &_qualityLevel, 10000, OpticalFlowMotionDetection::onChange2, this);
    createTrackbar("Min distance", windowTitle + suffix, &_minDistance, 100, OpticalFlowMotionDetection::onChange3, this);
    createTrackbar("Trail size", windowTitle + suffix, &trailSize, 100);
}


void OpticalFlowMotionDetection::onChange1(int c, void *p) {
    OpticalFlowMotionDetection *w = (OpticalFlowMotionDetection *) p;
    w->reset();
}

void OpticalFlowMotionDetection::onChange2(int c, void *p) {
    OpticalFlowMotionDetection *w = (OpticalFlowMotionDetection *) p;
    w->qualityLevel = (double) (1.0 + w->_qualityLevel) / 10000;
    w->reset();
}

void OpticalFlowMotionDetection::onChange3(int c, void *p) {
    OpticalFlowMotionDetection *w = (OpticalFlowMotionDetection *) p;
    w->minDistance = (double) w->image_prev.cols * w->_minDistance / 100;
    w->reset();
}