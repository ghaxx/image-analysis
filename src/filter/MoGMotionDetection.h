//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include <opencv2/video/background_segm.hpp>
#include "Transformation.h"

#ifndef __MoGMotionDetection_H_
#define __MoGMotionDetection_H_


class MoGMotionDetection : public Transformation {
    int history;
    int nMixtures;
    double backgroundRatio;
    float threshold;
    int _threshold;
    int _backgroundRatio;

    cv::BackgroundSubtractorMOG2 *backgroundSubtractorMOG2;
public:

    MoGMotionDetection();

    virtual cv::Mat transform(cv::Mat image);

    void createControls(const std::string &windowTitle);
    static void onChange1(int c, void *p);
    static void onChange2(int c, void *p);
    static void onChange3(int c, void *p);
    static void onChange4(int c, void *p);

    void reset();
};


#endif //__MoGMotionDetection_H_
