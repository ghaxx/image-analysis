//
// Created by Kuba Sławiński on 18/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#ifndef __VideoWindow_H_
#define __VideoWindow_H_

#import "DisplayWindow.h"

class VideoWindow : public DisplayWindow {
    cv::VideoCapture* capture;
    int frameNumber;

public:
    VideoWindow(std::string title, std::string path);

    virtual ~VideoWindow();

    virtual void show() override;
};


#endif //__VideoWindow_H_
