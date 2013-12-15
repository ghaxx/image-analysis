//
// Created by Kuba Sławiński on 06/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"

#ifndef __Ex8Generic_H_
#define __Ex8Generic_H_


class Ex8Generic :public DisplayWindow {
protected:

    cv::VideoCapture *capture;
    cv::Mat background;
    int learningRate;
    int thresh;
    cv::Mat accumulated;

public:
    Ex8Generic(const std::string &title);

    virtual void show() override;

};


#endif //__Ex8Generic_H_
