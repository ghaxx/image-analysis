//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "CameraFilterWindow.h"
#include "HaarFaceTransformation.h"

#ifndef __HaarFaceWindow_H_
#define __HaarFaceWindow_H_


class HaarFaceWindow : public CameraFilterWindow {
    int scaleFactor;
    int minNeighbors;
    int minSize;

public:
    HaarFaceWindow(const std::string &title);

    virtual HaarFaceTransformation* getTransformation();
};


#endif //__HaarFaceWindow_H_
