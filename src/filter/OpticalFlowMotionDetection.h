//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __OpticalFlowMotionDetection_H_
#define __OpticalFlowMotionDetection_H_


class OpticalFlowMotionDetection : public Transformation {
    cv::Mat image_prev, image_next;
    std::vector<cv::Point2f> features_prev, features_next;
    std::vector<unsigned char> status;
    std::vector<float> err;

public:

    OpticalFlowMotionDetection();

    virtual cv::Mat transform(cv::Mat image);
    int maxCorners;
    double qualityLevel;
    double minDistance;

    void reset();
};


#endif //__OpticalFlowMotionDetection_H_
