//
// Created by Kuba Sławiński on 10/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __Util_H_
#define __Util_H_

#include <opencv2/opencv.hpp>

class Util {
public:
    static void addAlphaMat(cv::Mat &src, cv::Mat &dst);

    static void addAlphaMat(cv::Mat &src, cv::Mat &dst, double alpha);

    static void pictureInPicture(cv::Mat &source, cv::Mat &destination, int x, int y, int w, int h);

    static std::string intToString(int number);
};


#endif //__Util_H_
