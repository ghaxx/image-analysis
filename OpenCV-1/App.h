//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __App_H_
#define __App_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

#include <opencv/cv.h>
#include <opencv/highgui.h>
#import "LinearTransformation.h"
#import "ImageWindow.h"


class App {
    bool done;
    LinearTransformation *t;
    std::vector<ImageWindow> windows;

    public:
    App();

    void run();

    void catchAction();

    cv::Mat filterGrayScale(cv::Mat image);

    cv::Mat filterNegative(cv::Mat image);

    void reset();

    void registerWindow(ImageWindow *window);
};


#endif //__App_H_
