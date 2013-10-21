//
// Created by Kuba Sławiński on 18/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __CameraCaptureWindow_H_
#define __CameraCaptureWindow_H_

#import "DisplayWindow.h"


class CameraCaptureWindow : public ImageWindow {
    bool captureFrame;
    clock_t start;

    SynchronizedVideoCapture capture;

public:
    CameraCaptureWindow(std::string title);

    virtual void show() override;

    virtual void control(char key) override;

    double timeout;
};


#endif //__CameraCaptureWindow_H_
