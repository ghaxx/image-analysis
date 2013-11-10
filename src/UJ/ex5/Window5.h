//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "Util.h"

#ifndef __Window5_H_
#define __Window5_H_


class Window5 : public DisplayWindow {
    cv::Mat image;
    cv::Mat result;
    cv::Mat background;
    bool diffWithPrevious;
    cv::VideoCapture *capture;
    cv::VideoWriter *writer;
    bool record = false;
    bool morph;
    int blurRadius;
    int thresholdMin;
public:
    virtual void show() override;

    Window5(std::string title = "Window 5");

    virtual void control(char key) override;

    virtual ~Window5();

    void extractShapesInBinaryByDifference(cv::Mat &image, cv::Mat &thresh);

    void addContours(cv::Mat &source, cv::Mat &dest);

    void findHull(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void setThresholdMin(int thresholdMin);

    void setBlurRadius(int blurRadius);
};


#endif //__Window5_H_
