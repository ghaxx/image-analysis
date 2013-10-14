//
// Created by Kuba Sławiński on 11/10/2013.
// Copyright (c) 2013 Kuba Sławiński. All rights reserved.
//
// To change the template use AppCode | Preferences | File Templates.
//


#include "Negative.h"

void filterWindow::Negative::show(cv::Mat mat) {
    ImageWindow::show(mat);
}

filterWindow::Negative::Negative(std::string title) : ImageWindow(title) {

}
