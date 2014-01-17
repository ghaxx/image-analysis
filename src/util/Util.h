//
// Created by Kuba Sławiński on 10/11/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __Util_H_
#define __Util_H_

#include <opencv2/opencv.hpp>

class Util {
    static std::map<std::string, int*> trackbarValues;

public:

    static void trackbarChanged(int c, void *p);
    static void createTrackbar(std::string& trackbarName, std::string& windowName,
                                  double* value, int count, int factor,
                                  cv::TrackbarCallback onChange = 0,
                                  void* userdata = 0);

    static void addAlphaMat(cv::Mat &src, cv::Mat &dst);

    static void addAlphaMat(cv::Mat &src, cv::Mat &dst, double alpha);

    static void pictureInPicture(cv::Mat &source, cv::Mat &destination, int x, int y, int width = 0, int height = 0, int offsetX = 0, int offsetY = 0, int sourceW = 0, int sourceH = 0);

    static std::string intToString(int number);

    static void addFrame(cv::Mat &dest, int width, cv::Scalar &color);
    static void resizeCanvas(cv::Mat &source, cv::Mat &canvas, int width, cv::Scalar &color);

    static int quickDistance(cv::Point x1, cv::Point x2);
};


#endif //__Util_H_
