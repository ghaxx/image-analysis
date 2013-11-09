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

    void extractShapesInBinary(cv::Mat &image, cv::Mat &thresh);

//    void onMouse( int event, int x, int y, int c, void* p);

    void addContours(cv::Mat &source, cv::Mat &dest);

    void findHull(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void addBoundingBox(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void findCenterOfObject(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void drawObject(int x, int y, cv::Mat &frame);

    void addAlphaMat(cv::Mat &src, cv::Mat &dst);

    void addAlphaMat(cv::Mat &src, cv::Mat &dst, double alpha);

    void pictureInPicture(cv::Mat &source, cv::Mat &destination, int x, int y, int w, int h);

    std::string intToString(int number);

    cv::Mat const & getResult() const;

    int getMinHue() const;

    void setMinHue(int minHue);

    int getMaxHue() const;

    void setMaxHue(int maxHue);

    int getBlurRadius() const;

    void setBlurRadius(int blurRadius);

    static bool sortConvDef(cv::Vec<int, 4> &p1, cv::Vec<int, 4> &p2);
};


#endif //__SeeHandWindow_H_
