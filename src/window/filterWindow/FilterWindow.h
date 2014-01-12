//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#ifndef __FilterWindow_H_
#define __FilterWindow_H_

#import "DisplayWindow.h"
#import "Transformation.h"

class FilterWindow : public DisplayWindow {
    Transformation* t;

protected:
    FilterWindow(std::string title, Transformation *transformation);

public:
    virtual ~FilterWindow();

    virtual Transformation* getT() const;

    virtual void preprocess(cv::Mat &image);
    virtual void postprocess(cv::Mat &image, cv::Mat &transformed);
};


#endif //__FilterWindow_H_
