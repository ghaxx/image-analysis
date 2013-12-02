//
// Created by Kuba Sławiński on 29/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "CameraFilterWindow.h"

#ifndef __Ex7Gauss_H_
#define __Ex7Gauss_H_


class Ex7Contours : public DisplayWindow {

    SynchronizedVideoCapture* capture;

    int minThreshold;
    int maxThreshold;
    int blurRadius;
    int maskSize;
public:
    Ex7Contours(std::string title);

    virtual void show();
};


#endif //__Ex7Gauss_H_
