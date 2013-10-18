//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//



#ifndef __LinearTransformation_H_
#define __LinearTransformation_H_

#import "Transformation.h"


class LinearTransformation : public Transformation {

    public:

    int add;
    float mult;

    LinearTransformation();
    virtual cv::Mat transform(cv::Mat image);

};


#endif //__LinearTransformation_H_
