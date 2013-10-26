//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __Negative_H_
#define __Negative_H_

#import "FilterWindow.h"
#import "LinearTransformation.h"

class ManipulationWindow : public FilterWindow {
    SynchronizedVideoCapture *capture;

public:
    ManipulationWindow(const char* title);

    virtual void show() override;

    virtual void control(char key) override;

    void reset();

    LinearTransformation *getLT();
};


#endif //__Negative_H_
