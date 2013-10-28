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
    std::string title;
    App* app;

protected:
    DisplayWindow(std::string title);

public:
    virtual void show() = 0;

    virtual void control(char key);

    App * getApp() const;

    void setApp(App *app);

    std::string getTitle() const;

    virtual ~DisplayWindow();
};


#endif //__ImageWindow_H_
