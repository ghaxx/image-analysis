//
// Created by Kuba Sławiński on 26/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "ImageFilterWindow.h"

#ifndef __HandImageWindow_H_
#define __HandImageWindow_H_


class HandImageWindow : public ImageFilterWindow {
    int counter;
public:
    HandImageWindow(const std::string &title);


    virtual void control(char key) override;
};


#endif //__HandImageWindow_H_
