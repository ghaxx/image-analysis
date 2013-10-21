//
// Created by Kuba Sławiński on 21/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __Camera_H_
#define __Camera_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>


class SynchronizedVideoCapture : public cv::VideoCapture {
    static bool readNew;
    cv::Mat lastRead;

public:

    SynchronizedVideoCapture();

    virtual bool read(cv::Mat &image) override;

    void refresh();

};


#endif //__Camera_H_
