//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "CameraFilterWindow.h"
#include "OpticalFlowMotionDetection.h"

#ifndef __MotionDetection11CameraWindow_H_
#define __MotionDetection11CameraWindow_H_


class MotionDetection11CameraWindow : public CameraFilterWindow {

public:
    MotionDetection11CameraWindow(const std::string &title);

    virtual void postprocess(cv::Mat &image, cv::Mat &transformed) override;

    OpticalFlowMotionDetection* getTransformation();
};


#endif //__MotionDetection11CameraWindow_H_
