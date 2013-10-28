//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Image4.h"
#include "Lightness.h"
#include "SharpenWithMatrix.h"
#include "AppConfig.h"
#include "FilterChain.h"

using namespace std;

Image4::Image4():ImageFilterWindow("Zamek", "/Users/ghaxx/4.jpg", new FilterChain(3, new LinearTransformation(), new Lightness(), new SharpenWithMatrix())) {
}

void Image4::control(char key) {
    if (key == 'q')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->add += 10;
    if (key == 'a')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->add -= 10;
    if (key == 'w')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->mult += 0.1;
    if (key == 's')
        ((LinearTransformation *) (((FilterChain*) this->getT())->getTransformations()->at(0)))->mult -= 0.1;
    if (key == 'e')
        ((SharpenWithMatrix *) (((FilterChain*) this->getT())->getTransformations()->at(2)))->mult += 0.1;
    if (key == 'd')
        ((SharpenWithMatrix *) (((FilterChain*) this->getT())->getTransformations()->at(2)))->mult -= 0.1;
    if (key == ' ')
        saveImage();

    if (key != '\xff')
        refresh();
}

void Image4::saveImage() {
    cv::Mat transformed(getT()->transform(getImage()));

    vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(80);
    char name[100];
    sprintf(name, "%s/zamek_%li.jpg", AppConfig::outputDir, time(0));
    imwrite(name, transformed, params);
    transformed.release();
}
