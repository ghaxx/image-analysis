//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "CameraFilterWindow.h"
#include "MoGMotionDetection.h"

#ifndef __MoGMotionDetectionCameraWindow_H_
#define __MoGMotionDetectionCameraWindow_H_


class MoGMotionDetectionCameraWindow : public CameraFilterWindow {

public:
    MoGMotionDetectionCameraWindow(const std::string &title);

    MoGMotionDetection* getTransformation();
};


#endif //__MoGMotionDetectionCameraWindow_H_
