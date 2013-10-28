//
// Created by Kuba Sławiński on 28/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "FilterChain.h"

using namespace cv;
using namespace std;

typedef Transformation* TYPE_TR_PTR;

Mat FilterChain::transform(Mat image) {
    Mat transformed(image);

    for (std::vector<Transformation *>::iterator it = transformations->begin(); it != transformations->end(); ++it) {
        transformed = (*it)->transform(transformed);
    }

    return transformed;
}

FilterChain::FilterChain(vector<Transformation *> *transformations) {
    this->transformations = transformations;
}

FilterChain::FilterChain(int count, ...) {
    transformations = new std::vector<Transformation *>();
    va_list arguments;
    va_start(arguments, count);
    for (int i = 0; i < count; i++)
        transformations->push_back(va_arg(arguments, TYPE_TR_PTR));
}

std::vector<Transformation *> *FilterChain::getTransformations() const {
    return transformations;
}