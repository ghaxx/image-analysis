//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __App_H_
#define __App_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <math.h>

//#include <opencv/cv.h>
//#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>

#import "LinearTransformation.h"
#import "DisplayWindow.h"
#include "SynchronizedVideoCapture.h"

class App {
    static const int logLevel = 0;
    bool done;
    std::vector<DisplayWindow *> windows;
    double timeout;
    SynchronizedVideoCapture* capture;

public:
    App();

    void run();

    void catchAction();

    void registerWindow(DisplayWindow *window);

    static void debug(const char *format, ...);
};


#endif //__App_H_
