//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "CameraCaptureWindow.h"
#include "CameraFilterWindow.h"
#include "SharpenWithMatrix.h"
#include "Lightness.h"

#ifndef __Window4_H_
#define __Window4_H_

class Camera4 : public CameraFilterWindow {
    bool record;
    cv::VideoWriter* writer;

public:

    Camera4();

    virtual ~Camera4();

    virtual void control(char key) override;

    virtual void postprocess(cv::Mat &image, cv::Mat &transformed) override;
};


#endif //__Window4_H_
