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

    static void pictureInPicture(cv::Mat &source, cv::Mat &destination, int x, int y, int width, int height, int offsetX = 0, int offsetY = 0, int sourceW = 0, int sourceH = 0);

    static std::string intToString(int number);

    static void addFrame(cv::Mat &dest, int width, cv::Scalar &color);
    static void resizeCanvas(cv::Mat &source, cv::Mat &canvas, int width, cv::Scalar &color);
};


#endif //__Util_H_
