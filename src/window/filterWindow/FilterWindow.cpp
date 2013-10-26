//
// Created by Kuba Sławiński on 16/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//


#import "FilterWindow.h"
#import "App.h"


FilterWindow::FilterWindow(const char* title, std::vector<Transformation*>* t):DisplayWindow(title) {
    this->t = t;
}

FilterWindow::~FilterWindow() {
    delete t;
}

std::vector<Transformation*>* FilterWindow::getT() const {
    return t;
}

FilterWindow::FilterWindow(const char* title, Transformation* transformation):DisplayWindow(title) {
    this->t = new std::vector<Transformation*>();
    this->t->push_back(transformation);
}
