//
// Created by Kuba Sławiński on 28/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Video4.h"
#include "AppConfig.h"
#include "FilterChain.h"
#include "Lightness.h"
#include "SharpenWithMatrix.h"
#include "TransformVideo.h"

using namespace cv;

Video4::Video4():VideoFilterWindow("Roboty", (AppConfig::inputDir + "/4.avi").c_str(), new FilterChain(3, new LinearTransformation(), new Lightness(), new SharpenWithMatrix())) {
    record = false;
    writer = new VideoWriter();
}

void Video4::control(char key) {
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
    if (key == ' ')
        startRecording();
    if (key == 'v')
        transformVideo();
}

void Video4::transformVideo() {
    char name[100];
    sprintf(name, (AppConfig::outputDir + "/4_%li.avi").c_str(), time(0));
    new TransformVideo(getT(), path, string(name));
}

void Video4::startRecording() {
    record = !record;
    capture->set(CV_CAP_PROP_POS_AVI_RATIO , 0);

    if (record) {
        double width = capture->get(CV_CAP_PROP_FRAME_WIDTH);
        double height = capture->get(CV_CAP_PROP_FRAME_HEIGHT);
        double fps = capture->get(CV_CAP_PROP_FPS);
        int fourcc = (int) capture->get(CV_CAP_PROP_FOURCC);
        fourcc = 0;

        char name[100];
        sprintf(name, (AppConfig::outputDir + "/4_%li.avi").c_str(), time(0));
        writer->open(name, fourcc, fps, Size(width, height), true);
    }
}

void Video4::postprocess(cv::Mat &image, cv::Mat &transformed) {
    if (record) {
        writer->write(image);
        cv::putText(image, "Recording", cvPoint(10, 30), cv::FONT_HERSHEY_COMPLEX_SMALL, 0.8, cvScalar(0, 0, 0), 1, CV_AA);
    }
}
