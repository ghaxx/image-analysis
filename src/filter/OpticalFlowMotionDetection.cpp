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
    maxCorners = 250;
    qualityLevel = 0.0001;
    minDistance = 1;
    found = 0;

    _qualityLevel = (int) qualityLevel * 10000 - 1;
    _minDistance = (int) minDistance;
}

cv::Mat OpticalFlowMotionDetection::transform(Mat image) {
    int foundNow = 0;
    if (image_next.empty() || features_next.size() == 0) {
        printf("Initializing corners\n");
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

        for (int i = 0; i < status.size(); i++) {
            Point2i pt1 = Point(features_first[i].x, features_first[i].y);
            Point2i pt2 = Point(features_next[i].x, features_next[i].y);
            Point2i pt3 = Point(features_prev[i].x, features_prev[i].y);
            if ((int) status[i] == 1 && Util::quickDistance(pt2, pt3) > 2) {
                foundNow++;
                line(image, pt1, pt2, Scalar(0, 0, 0), 2);
                circle(image, pt2, 2, Scalar(0, 0, 0), -1);

                line(image, pt1, pt2, Scalar(255, 255, 255), 1);
                circle(image, pt2, 1, Scalar(255, 255, 255), -1);
            }
        }

        if (foundNow < (float) found / 2 || foundNow == 0) {
            printf("Found not enough points: %d <  %d / 2\n", foundNow, found);
            reset();
            return image;
        }
    }
    image_prev = image_next.clone();
    features_prev = features_next;
    found = foundNow;
    return image;
}

void OpticalFlowMotionDetection::reset() {
    printf("Reset\n");
    image_prev.release();

    features_prev.clear();
    features_next.clear();

    found = 0;
}

void OpticalFlowMotionDetection::createControls(const std::string &windowTitle) {
    createTrackbar("Max Corners", windowTitle, &maxCorners, 400, OpticalFlowMotionDetection::onChange1, this);
    createTrackbar("Quality level", windowTitle, &_qualityLevel, 10000, OpticalFlowMotionDetection::onChange2, this);
    createTrackbar("Min distance", windowTitle, &_minDistance, 100, OpticalFlowMotionDetection::onChange3, this);
}


void OpticalFlowMotionDetection::onChange1(int c, void *p) {
    OpticalFlowMotionDetection *w = (OpticalFlowMotionDetection *) p;
    w->maxCorners = w->maxCorners;
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