//
// Created by Kuba Sławiński on 01/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"

#ifndef __SeeHandWindow_H_
#define __SeeHandWindow_H_


class SeeHandWindow: public DisplayWindow {
    cv::Mat image;
    cv::Mat result;
    SynchronizedVideoCapture* capture;
    cv::VideoWriter* writer;
    bool record = false;
    int minHue;
    int maxHue;
    bool morph;
    int blurRadius;
public:
    virtual void show() override;

    SeeHandWindow(std::string title = "Hand");

    virtual void control(char key) override;

    virtual ~SeeHandWindow();

    void findObjects(cv::Mat &image);

//    void onMouse( int event, int x, int y, int c, void* p);

    cv::Mat const & getResult() const;

    int getMinHue() const;

    void setMinHue(int minHue);

    int getMaxHue() const;

    void setMaxHue(int maxHue);

    int getBlurRadius() const;

    void setBlurRadius(int blurRadius);
};


#endif //__SeeHandWindow_H_
