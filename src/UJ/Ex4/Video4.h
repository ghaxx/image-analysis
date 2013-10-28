//
// Created by Kuba Sławiński on 28/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "VideoFilterWindow.h"

#ifndef __Video4_H_
#define __Video4_H_


class Video4 : public VideoFilterWindow {
    bool record;
    cv::VideoWriter* writer;

public:
    Video4();

    void startRecording();
    void transformVideo();

    virtual void control(char key) override;

    virtual void postprocess(cv::Mat &image) override;
};


#endif //__Video4_H_
