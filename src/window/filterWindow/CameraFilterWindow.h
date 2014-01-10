//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "FilterWindow.h"

#ifndef __CameraFilterWindow_H_
#define __CameraFilterWindow_H_


class CameraFilterWindow : public FilterWindow {
    int number;
    SynchronizedVideoCapture *capture;
    bool record;
    cv::VideoWriter* writer;

public:
    CameraFilterWindow(std::string title, Transformation* transformation);

    virtual void show() override;


    virtual void control(char key) override;
};


#endif //__CameraFilterWindow_H_
