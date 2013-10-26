//
// Created by Kuba Sławiński on 25/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#include "Window4.h"

Window4::Window4():CameraFilterWindow("Camera - sharpened", new std::vector<Transformation*>()) {
    getT()->push_back(new LinearTransformation());
    getT()->push_back(new Lightness());
    getT()->push_back(new SharpenWithMatrix());
}

void Window4::control(char key) {
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
}
