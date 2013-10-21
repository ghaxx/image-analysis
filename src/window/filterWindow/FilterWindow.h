//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#ifndef __FilterWindow_H_
#define __FilterWindow_H_

#import "DisplayWindow.h"
#import "Transformation.h"

class FilterWindow : public DisplayWindow {
    Transformation *t;

    SynchronizedVideoCapture* capture;
public:

    FilterWindow(const std::string title, Transformation *t);

    virtual ~FilterWindow();


    virtual void show() override;


    Transformation *getT() const;
};


#endif //__FilterWindow_H_
