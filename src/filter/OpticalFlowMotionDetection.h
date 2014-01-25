//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"
#include <list>
#include <boost/progress.hpp>

#ifndef __OpticalFlowMotionDetection_H_
#define __OpticalFlowMotionDetection_H_


class OpticalFlowMotionDetection : public Transformation {
    cv::Mat image_prev, image_next;
    std::vector<cv::Point2f> features_prev, features_next, features_first;
    std::vector<unsigned char> status;
    std::vector<float> err;
	std::list<cv::Mat> lines;
    int found;
	int trailSize;

public:

    OpticalFlowMotionDetection();

    virtual cv::Mat transform(cv::Mat image);
    int maxCorners;
    double qualityLevel;
    double minDistance;


    int _qualityLevel;
    int _minDistance;

    void reset();

    void createControls(const std::string &windowTitle);
    static void onChange1(int c, void *p);
    static void onChange2(int c, void *p);
    static void onChange3(int c, void *p);
};


#endif //__OpticalFlowMotionDetection_H_