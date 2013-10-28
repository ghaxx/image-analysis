//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Window4.h"
#include "FilterChain.h"
#include "AppConfig.h"

using namespace cv;

Window4::Window4():CameraFilterWindow("Camera - sharpened", new FilterChain(3, new LinearTransformation(), new Lightness(), new SharpenWithMatrix())) {
    record = false;
}

void Window4::control(char key) {
    if (key == 'q')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->add += 10;
    if (key == 'a')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->add -= 10;
    if (key == 'w')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->mult += 0.1;
    if (key == 's')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->mult -= 0.1;
    if (key == 'e')
        ((SharpenWithMatrix *) (((FilterChain*) this->getT())->getTransformations()->at(2)))->mult += 0.1;
    if (key == 'd')
        ((SharpenWithMatrix *) (((FilterChain*) this->getT())->getTransformations()->at(2)))->mult -= 0.1;
    if (key == ' ') {
        record = !record;
        if (record) {
            printf("Recording started\n");
            char name[100];
            sprintf(name, (AppConfig::inputDir + "/camera%li.avi").c_str(), time(0));
            writer->open(name, 0, 15.0, Size(640, 480), true);
        } else {
            printf("Recording ended\n");
            writer->release();
        }
    }
}

void Window4::postprocess(cv::Mat &image) {
    if (record) {
        cv::putText(image, "Recording...", cvPoint(10, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(255, 255, 255), 1, CV_AA);
    }
}
