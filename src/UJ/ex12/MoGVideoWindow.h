//
// Created by Kuba Sławiński on 17/01/2014.
// Copyright (c) 2014 Kuba Sławiński. All rights reserved.
//



#include "VideoFilterWindow.h"
#include "MoGMotionDetection.h"

#ifndef __MoGVideoWindow_H_
#define __MoGVideoWindow_H_


class MoGVideoWindow : public VideoFilterWindow {
public:

    MoGVideoWindow(const std::string &title, const std::string &path);

    MoGMotionDetection* getTransformation();
};


#endif //__MoGVideoWindow_H_
