//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"

#ifndef __Window5_H_
#define __Window5_H_


class Window5: public DisplayWindow {
    cv::Mat image;
    cv::Mat result;
    cv::Mat background;
    bool diffWithPrevious;
    cv::VideoCapture* capture;
    cv::VideoWriter* writer;
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

    cv::Mat const & getResult() const;

    int getBlurRadius() const;

    void setBlurRadius(int blurRadius);

    std::string intToString(int number);

    void pictureInPicture(cv::Mat &source, cv::Mat &destination, int x, int y, int w, int h);

    void addAlphaMat(cv::Mat &src, cv::Mat &dst, double alpha);

    void addAlphaMat(cv::Mat &src, cv::Mat &dst);

    void addContours(cv::Mat &source, cv::Mat &dest);

    void findHull(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    int getThresholdMin() const;

    void setThresholdMin(int thresholdMin);
};


#endif //__Window5_H_
