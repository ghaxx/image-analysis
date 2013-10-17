//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __Negative_H_
#define __Negative_H_

#include <iostream>
#import "FilterWindow.h"
#import "LinearTransformation.h"

namespace filterWindow {
    class ManipulationWindow : public FilterWindow {

    public:

        ManipulationWindow(std::string title);

        virtual void show(cv::Mat mat) override;

        virtual void control(char key) override;

        void reset();

        LinearTransformation* getLT();
    };
}


#endif //__Negative_H_
