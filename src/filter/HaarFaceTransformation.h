//
// Created by Kuba Sławiński on 11/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __HaarFaceTransformation_H_
#define __HaarFaceTransformation_H_


class HaarFaceTransformation : public Transformation {
//    cv::CascadeClassifier *classifier;
    cv::CascadeClassifier **classifiers;
    std::string *items;
public:
    double scaleFactor;
    int minNeighbors;
    cv::Size minSize;
    int _scaleFactor;
    int _minSize;

    HaarFaceTransformation();

    virtual cv::Mat transform(cv::Mat image);

    void createControls(std::string windowTitle);

    static void onChange1(int c, void *p);
    static void onChange2(int c, void *p);
    static void onChange3(int c, void *p);
};


#endif //__HaarFaceTransformation_H_
