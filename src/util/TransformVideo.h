//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"

#ifndef __TransformVideo_H_
#define __TransformVideo_H_


class TransformVideo {
    int number;
    Transformation** transformations;
    const char* source;
    const char* dest;
public:

    TransformVideo(int number, Transformation **transformations, char const *source, char const *dest);
};


#endif //__TransformVideo_H_
