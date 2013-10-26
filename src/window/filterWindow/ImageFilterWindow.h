//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "FilterWindow.h"

#ifndef __ImageFilterWindow_H_
#define __ImageFilterWindow_H_


class ImageFilterWindow : public FilterWindow {
    const char *imageFile;
    cv::Mat image;
    bool _refresh;
public:
    ImageFilterWindow(const char* title, char const *imageFile, std::vector<Transformation *> *transformations);

    virtual void show() override;

    void refresh();

    cv::Mat const &getImage() const;
};


#endif //__ImageFilterWindow_H_
