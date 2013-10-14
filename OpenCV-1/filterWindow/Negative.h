//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//



#ifndef __Negative_H_
#define __Negative_H_

#include <iostream>
#import "ImageWindow.h"

namespace filterWindow {
    class Negative : public ImageWindow {
    public:
        virtual void show(cv::Mat mat);

        Negative(std::string title);
    };
}


#endif //__Negative_H_
