//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __ImageWindow_H_
#define __ImageWindow_H_

#include <iostream>
#include <string>
#include <math.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>


class ImageWindow {
    std::string title;

    public:
    ImageWindow(std::string title);

    virtual void show(cv::Mat mat);

    virtual void control(char key);
};


#endif //__ImageWindow_H_
