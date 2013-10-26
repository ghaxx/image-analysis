//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Image4.h"
#include "Lightness.h"
#include "SharpenWithMatrix.h"
#include "AppConfig.h"

using namespace std;

Image4::Image4():ImageFilterWindow("Zamek", "/Users/ghaxx/4.jpg", new vector<Transformation *>()) {
    getT()->push_back(new LinearTransformation());
    getT()->push_back(new Lightness());
    getT()->push_back(new SharpenWithMatrix());
}

void Image4::control(char key) {
    if (key == 'q')
        ((LinearTransformation *) (this->getT()->at(0)))->add += 10;
    if (key == 'a')
        ((LinearTransformation *) (this->getT()->at(0)))->add -= 10;
    if (key == 'w')
        ((LinearTransformation *) (this->getT()->at(0)))->mult += 0.1;
    if (key == 's')
        ((LinearTransformation *) (this->getT()->at(0)))->mult -= 0.1;
    if (key == 'e')
        ((SharpenWithMatrix *) (this->getT()->at(2)))->mult += 0.1;
    if (key == 'd')
        ((SharpenWithMatrix *) (this->getT()->at(2)))->mult -= 0.1;
    if (key == ' ')
        saveImage();

    if (key != '\xff')
        refresh();
}

void Image4::saveImage() {
    cv::Mat transformed(getImage());

    for (std::vector<Transformation *>::iterator it = getT()->begin(); it != getT()->end(); ++it) {
        transformed = (*it)->transform(transformed);
    }

    vector<int> params;
    params.push_back(CV_IMWRITE_JPEG_QUALITY);
    params.push_back(80);
    char name[100];
    sprintf(name, "%s/zamek_%li.jpg", AppConfig::outputDir, time(0));
    imwrite(name, transformed, params);
    transformed.release();
}
