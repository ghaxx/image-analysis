//
// Created by Kuba Sławiński on 25/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"
#include "OpticalFlowMotionDetection.h"

#ifndef __FindHand_H_
#define __FindHand_H_


class FindHand : public Transformation {
public:
    cv::Mat image;
    cv::Mat result;
    bool record;
    int minHue;
    int maxHue;
    int minSaturation;
    int maxSaturation;
    int minValue;
    int maxValue;
    int blurRadius;

    float shapeRadius;

    int cols;
    int rows;
    std::string title;
    int center_x;
    int center_y;
    cv::Point center;
    int handScale;

    OpticalFlowMotionDetection* motionDetection;

    void extractShapesInBinary(cv::Mat &image, cv::Mat &thresh);

    //    void onMouse( int event, int x, int y, int c, void* p);

    void addContours(cv::Mat &source, cv::Mat &dest);

    void findHull(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void addBoundingBox(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void findCenterOfObject(std::vector<cv::Point_<int> > &contour, cv::Mat &dest);

    void drawObject(int x, int y, cv::Mat &frame);

    cv::Mat const &getResult() const;

    int getMinHue() const;

    void setMinHue(int minHue);

    int getMaxHue() const;

    void setMaxHue(int maxHue);

    int getBlurRadius() const;

    void setBlurRadius(int blurRadius);

    static bool sortConvDef(cv::Vec<int, 4> &p1, cv::Vec<int, 4> &p2);


    int getMinSaturation() const;

    void setMinSaturation(int minSaturation);

    int getMaxSaturation() const;

    void setMaxSaturation(int maxSaturation);

    int getMinValue() const;

    void setMinValue(int minValue);

    int getMaxValue() const;

    void setMaxValue(int maxValue);

public:

    virtual cv::Mat transform(cv::Mat image);

    void createControls(const std::string &windowTitle);

    std::string getTitle();

    FindHand();

    double approxPolyEpsilon;
    int drawAll;
};


#endif //__FindHand_H_
