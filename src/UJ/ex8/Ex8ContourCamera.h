//
// Created by Kuba Sławiński on 06/12/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "DisplayWindow.h"
#include "Ex8Generic.h"

#ifndef __Ex8ContourCamera_H_
#define __Ex8ContourCamera_H_


class Ex8ContourCamera : public Ex8Generic {

public:
    Ex8ContourCamera(const std::string &title);

    virtual void control(char key) override;
    void refreshBackground();
};


#endif //__Ex8ContourCamera_H_
