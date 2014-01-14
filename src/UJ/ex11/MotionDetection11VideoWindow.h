//
// Created by Kuba Sławiński on 12/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "VideoFilterWindow.h"
#include "OpticalFlowMotionDetection.h"

#ifndef __MotionDetection11VideoWindow_H_
#define __MotionDetection11VideoWindow_H_


class MotionDetection11VideoWindow : public VideoFilterWindow {

    int maxCorners;
    int qualityLevel;
    int minDistance;

public:
    MotionDetection11VideoWindow(const std::string &title, const std::string &path);

    OpticalFlowMotionDetection* getTransformation();
};


#endif //__MotionDetection11VideoWindow_H_
