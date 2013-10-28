//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "FilterWindow.h"

#ifndef __ImageFilterWindow_H_
#define __ImageFilterWindow_H_


class ImageFilterWindow : public FilterWindow {
    bool _refresh;
    cv::Mat image;

protected:
    const char *imageFile;

public:
    ImageFilterWindow(const char* title, char const *imageFile, Transformation* transformation);

    virtual void show() override;

    void refresh();

    cv::Mat const &getImage() const;
};


#endif //__ImageFilterWindow_H_
