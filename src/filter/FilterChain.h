//
// Created by Kuba Sławiński on 28/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#include "Transformation.h"
#include <vector>

#ifndef __FilterChain_H_
#define __FilterChain_H_


class FilterChain: public Transformation {
    std::vector<Transformation*>* transformations;

public:
    FilterChain(std::vector<Transformation*>* transformations);
    FilterChain(int count, ...);
    virtual cv::Mat transform(cv::Mat image);

    std::vector<Transformation *> * getTransformations() const;
};


#endif //__FilterChain_H_
