//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "ImageFilterWindow.h"

#ifndef __Image4_H_
#define __Image4_H_


class Image4:public ImageFilterWindow {
    bool save;
public:
    Image4();

    virtual void control(char key) override;

    void saveImage();

    virtual void postprocess(cv::Mat &image, cv::Mat &transformed) override;
};


#endif //__Image4_H_
