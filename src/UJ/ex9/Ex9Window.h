//
// Created by Kuba Sławiński on 13/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "CameraFilterWindow.h"
#include "FindLines.h"

#ifndef __Ex9Window_H_
#define __Ex9Window_H_


class Ex9Window : public CameraFilterWindow {
    cv::VideoCapture *capture;
public:
    Ex9Window(const std::string &title);

    FindLines *getFilter();

    int rho;
    int theta;
    int thresh;
    int minLineLength;
    int maxLineGap;

    static void onThreshChange(int c, void *p);

    static void onChange1(int c, void *p);

    static void onChange2(int c, void *p);

    static void onChange3(int c, void *p);

    static void onChange4(int c, void *p);
};


#endif //__Ex9Window_H_
