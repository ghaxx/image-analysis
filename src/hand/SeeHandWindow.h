//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "Util.h"
#include "CameraFilterWindow.h"
#include "FindHand.h"

#ifndef __SeeHandWindow_H_
#define __SeeHandWindow_H_


class SeeHandWindow: public CameraFilterWindow {

public:
    SeeHandWindow(const std::string &title);

    FindHand* getTransformation();

    void control(char key);
};


#endif //__SeeHandWindow_H_
