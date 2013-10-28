//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "FilterWindow.h"

#ifndef __VideoFilterWindow_H_
#define __VideoFilterWindow_H_


class VideoFilterWindow : public FilterWindow {
protected:
    const char* path;
    cv::VideoCapture *capture;

public:
    VideoFilterWindow(const char* title, char const *path, Transformation* transformation);

    virtual void show() override;
};


#endif //__VideoFilterWindow_H_
