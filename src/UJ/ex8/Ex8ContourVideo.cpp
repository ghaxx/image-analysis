//
// Created by Kuba Sławiński on 06/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Ex8ContourVideo.h"
#include "Util.h"

using namespace cv;

Ex8ContourVideo::Ex8ContourVideo(const std::string &title, std::string file):Ex8Generic(title) {
    capture = new cv::VideoCapture(file);
}