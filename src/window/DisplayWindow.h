//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __ImageWindow_H_
#define __ImageWindow_H_

#include <opencv/cv.h>
#import "main.h"
#include "App.h"
#include "SynchronizedVideoCapture.h"

class DisplayWindow {
    const char* title;
    App* app;

public:
    DisplayWindow(const char* title);

    virtual void show() = 0;

    virtual void control(char key);

    App * getApp() const;

    void setApp(App *app);

    const char* getTitle() const;

    virtual ~DisplayWindow();
};


#endif //__ImageWindow_H_
