//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "CameraFilterWindow.h"
#include "OpticalFlowMotionDetection.h"

#ifndef __MotionDetection11CameraWindow_H_
#define __MotionDetection11CameraWindow_H_


class MotionDetection11CameraWindow : public CameraFilterWindow {

    int maxCorners;
    int qualityLevel;
    int minDistance;

public:
    MotionDetection11CameraWindow(const std::string &title);

    virtual void postprocess(cv::Mat &image, cv::Mat &transformed) override;

    OpticalFlowMotionDetection* getTransformation();

    static void onChange1(int c, void *p);
    static void onChange2(int c, void *p);
    static void onChange3(int c, void *p);
};


#endif //__MotionDetection11CameraWindow_H_
